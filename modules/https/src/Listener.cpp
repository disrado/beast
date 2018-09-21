#include "https/Listener.hpp"

#include <boost/system/system_error.hpp>

namespace
{

void Fail(boost::system::error_code ec, char const* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
}

void Fail(char const* what)
{
	std::cerr << what << std::endl;
}

}

namespace https
{

Listener::Listener(boost::asio::io_context& ioc, tcp::endpoint endpoint)
	: m_acceptor(ioc)
	, m_socket(ioc)
{
	try
	{
		m_acceptor.open(endpoint.protocol());
		m_acceptor.set_option(boost::asio::socket_base::reuse_address(true));
		m_acceptor.bind(endpoint);
		m_acceptor.listen(boost::asio::socket_base::max_listen_connections);
	}
	catch(const boost::system::system_error& ex) {
		Fail(ex.what());
	}
}

// Start accepting incoming connections
void Listener::Run()
{
	if (!m_acceptor.is_open()) {
		return;
	}
	
	DoAccept();
}

void Listener::DoAccept()
{
	m_acceptor.async_accept(m_socket, [self = shared_from_this()] (boost::system::error_code ec) {
		self->OnAccept(ec);
	});
}

void Listener::OnAccept(boost::system::error_code ec)
{
	if (ec) {
		Fail(ec, "accept");
	} else {
		std::make_shared<Session>(std::move(m_socket))->Run();
	}

	// Accept another connection
	DoAccept();
}

}	// namespace https