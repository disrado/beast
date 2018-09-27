#include "app/ServerApp.hpp"

#include <utils/AppConfig.hpp>

#include <filesystem>

namespace app
{


ServerApp::ServerApp()
	: m_configPath{ "AppConfig.json" }
{
	utils::AppConfig::Instance().ReadConfig(m_configPath);
}


int ServerApp::Run()
{
	return https::Server(
		utils::AppConfig::Instance().server.host,
		utils::AppConfig::Instance().server.port,
		utils::AppConfig::Instance().server.threads
	).Run();
}

}	// namespace app