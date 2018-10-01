#include "https/Session.hpp"
#include "https/Router.hpp"

#include <utils/Exception.hpp>

#include <logger/Logger.hpp>

#include <boost/asio/bind_executor.hpp>


namespace https
{


Session::Session(tcp::socket socket)
	: m_socket{ std::move(socket) }
	, m_strand{ m_socket.get_executor() }
{
}


// Start the asynchronous operation
void Session::Run()
{
	// Make the request empty before reading,
	// otherwise the operation behavior is undefined.
	m_request = {};

	// Read a request
	http::async_read(m_socket, m_buffer, m_request,
		boost::asio::bind_executor(m_strand,
		[self = shared_from_this()] (const auto errorCode, const auto bt) {
			self->OnRead(errorCode, bt);
		})
	);
}


void Session::OnRead(boost::system::error_code ec, std::size_t bytes_transferred)
{
	lg::SLOG(lg::Severity::info, "Data transfering") << bytes_transferred << " bytes read";

	// This means they closed the connection
	if (ec == http::error::end_of_stream) {
		return DoClose();
	}

	if (ec) {
		lg::SLOG(lg::Severity::error, "Read") << ec.message();
		utils::Throw<std::logic_error>(ec.message());
	}

	auto response{ Router::Instance().GerHandler(
		m_request.target().to_string())->Handle(std::move(m_request))
	};

	m_response = response;

	http::async_write(m_socket, *response,
		boost::asio::bind_executor(m_strand,
			[s = shared_from_this(), close = response->need_eof()] (const auto ec, const auto bt) {
				s->OnWrite(ec, bt, close);
			}
		)
	);
}


void Session::OnWrite(boost::system::error_code ec, std::size_t bytes_transferred, bool close)
{
	if (ec)
	{
		lg::SLOG(lg::Severity::error, "Write") << ec.message();
		utils::Throw<std::logic_error>(ec.message());
	}

	lg::SLOG(lg::Severity::info, "Data transfering") << bytes_transferred << " bytes written";

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