#include "https/Server.hpp"
#include "https/Listener.hpp"

#include <memory>
#include <vector>
#include <thread>

namespace https
{
	
Server::Server(const Address& address, Port port, int threadNum)
    : m_address{ address }
    , m_port{ port }
    , m_threadsNum{ threadNum }
{}
	
int Server::Run()
{
	boost::asio::io_context ioc{ m_threadsNum };

	// Create and launch a listening port
	std::make_shared<https::Listener>(ioc, https::tcp::endpoint{ m_address, m_port })->Run();

	// Run the I/O service on the requested number of threads
	std::vector<std::thread> threads;
	threads.reserve(m_threadsNum - 1);

	for (auto i{ m_threadsNum - 1 }; i > 0; --i)
		threads.emplace_back([&ioc] { ioc.run(); });

	ioc.run();

	return EXIT_SUCCESS;
}

}	// namespace https