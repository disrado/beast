#pragma once

#include <memory>
#include <vector>
#include <thread>

#include "https/Listener.hpp"
#include "https/Types.hpp"

namespace https
{

class Server
{
public:
	Server(const Address& address, Port port, int threadNum);

	int Run();

private:
	Address m_address;
	Port m_port;
	int m_threadsNum;
};

}	// namespace https