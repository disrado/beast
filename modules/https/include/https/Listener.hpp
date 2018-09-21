#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <memory>

#include "Session.hpp"
#include "Types.hpp"

namespace https
{

// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener>
{
public:
	Listener(boost::asio::io_context& ioc, tcp::endpoint endpoint);

	void Run();

private:
	void DoAccept();
	void OnAccept(boost::system::error_code ec);

private:
	tcp::acceptor m_acceptor;
	tcp::socket m_socket;
};

}	// namespace https