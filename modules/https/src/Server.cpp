#include "https/Server.hpp"
#include "https/Listener.hpp"

#include <boost/asio/io_service.hpp>

#include <memory>
#include <vector>
#include <thread>


namespace https
{


Server::Server(const Host& host, Port port, int threadNum)
    : m_host{ host }
    , m_port{ port }
    , m_threadsNum{ threadNum }
{
}


int Server::Run()
{
	boost::asio::io_service ioc{ m_threadsNum };

	// Create and launch a listening port
	std::make_shared<https::Listener>(ioc, https::tcp::endpoint{ m_host, m_port })->Run();

	// Run the I/O service on the requested number of threads
	std::vector<std::thread> threads;
	threads.reserve(m_threadsNum);

	for (auto i{ 0 }; i < m_threadsNum; ++i) {
		threads.emplace_back([&ioc] { ioc.run(); });
	}

	ioc.run();

	return EXIT_SUCCESS;
}


}	// namespace https