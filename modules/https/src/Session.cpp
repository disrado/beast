#include "https/Session.hpp"

#include <boost/asio/bind_executor.hpp>

namespace
{

void fail(boost::system::error_code ec, char const* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
}

}

namespace https
{

Session::Session(tcp::socket socket)
	: m_socket(std::move(socket))
	, m_strand(m_socket.get_executor())
{
}

// Start the asynchronous operation
void Session::Run()
{
	// Make the request empty before reading,
	// otherwise the operation behavior is undefined.
	m_request = {};

	// Read a request
	http::async_read(m_socket, m_buffer, m_request, boost::asio::bind_executor(
		m_strand,
		std::bind(&Session::OnRead, shared_from_this(), std::placeholders::_1, std::placeholders::_2))
	);
}

void Session::OnRead(boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	// This means they closed the connection
	if (ec == http::error::end_of_stream) {
		return DoClose();
	}

	if (ec) {
		return fail(ec, "read");
	}

	auto responce{ std::make_shared<Response>(RequestHandler{}.HandleRquest(std::move(m_request))) };

	m_response = responce;

	http::async_write(
		m_socket,
		*responce,
		boost::asio::bind_executor(
			m_strand,
			[self = shared_from_this(), close = responce->need_eof()] (const auto errorCode, const auto bt) {
				self->OnWrite(errorCode, bt, close);
			}
		)
	);
}

void Session::OnWrite(boost::system::error_code ec, std::size_t bytes_transferred, bool close)
{
	boost::ignore_unused(bytes_transferred);

	if (ec) {
		return fail(ec, "write");
	}

	// This means we should close the connection, usually because
	// the response indicated the "Connection: close" semantic.
	if (close) {
		return DoClose();
	}

	// We're done with the response so delete it
	m_response = nullptr;

	// Read another request
	Run();
}

void Session::DoClose()
{
	// Send a TCP shutdown
	boost::system::error_code ec;
	m_socket.shutdown(tcp::socket::shutdown_send, ec);

	// At this point the connection is closed gracefully
}


}	// namespace https