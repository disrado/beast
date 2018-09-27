#include "app/ServerApp.hpp"

#include <utils/AppConfig.hpp>

#include <logger/Logger.hpp>


namespace app
{


ServerApp::ServerApp()
	: m_configPath{ "AppConfig.json" }
{
	utils::AppConfig::Instance().ReadConfig(m_configPath);

	logger::LOG(logger::Severity::info) << "Server configuration: "
		<< "\n\t   Host: " << utils::AppConfig::Instance().server.host
		<< "\n\t   Port: " << utils::AppConfig::Instance().server.port
		<< "\n\tThreads: " << utils::AppConfig::Instance().server.threads;
}


int ServerApp::Run()
{
	return https::Server{
		utils::AppConfig::Instance().server.host,
		utils::AppConfig::Instance().server.port,
		utils::AppConfig::Instance().server.threads
	}.Run();
}


}	// namespace app