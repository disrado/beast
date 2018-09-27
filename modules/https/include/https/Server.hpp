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
	Server(const std::string& host, Port port, int threadsNum);

	int Run();

private:
	Host m_host;
	Port m_port;
	int m_threadsNum;
};


}	// namespace https