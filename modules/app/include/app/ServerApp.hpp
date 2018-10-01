#pragma once

#include <https/Server.hpp>

#include <filesystem>


namespace app
{


class ServerApp
{
public:
	ServerApp();
	
	int Run();

private:
	void InitLogger();

private:
	const std::filesystem::path m_configPath;
};


}	// namespace app