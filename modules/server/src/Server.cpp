#include "server/Server.hpp"
#include "server/Listener.hpp"

#include <boost/asio/io_service.hpp>

#include <memory>
#include <vector>
#include <thread>


namespace bs
{


Server::Server(const std::string& host, Port port, int threadsNum)
	: m_host{ boost::asio::ip::make_address(host) }
	, m_port{ port }
	, m_threadsNum{ threadsNum }
{
}


int Server::Run()
{
	boost::asio::io_service ioc{ m_threadsNum };

	// Create and launch a listening port
	std::make_shared<bs::Listener>(ioc, bs::tcp::endpoint{ m_host, m_port })->Run();

	// Run the I/O service on the requested number of threads
	std::vector<std::thread> threads;
	threads.reserve(m_threadsNum);

	for (auto i{ 0 }; i < m_threadsNum; ++i) {
		threads.emplace_back([&ioc] { ioc.run(); });
	}

	ioc.run();

	return EXIT_SUCCESS;
}


}	// namespace bs