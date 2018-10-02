#include "app/ServerApp.hpp"

#include <utils/Config.hpp>

#include <logger/Logger.hpp>


namespace app
{


ServerApp::ServerApp()
	: m_configPath{ "AppConfig.json" }
{
	utils::AppConfig::Instance().ReadConfig(m_configPath);

	InitLogger();

	lg::LOG(lg::Severity::info) << "Server configuration: "
		<< "\n\t   Host: " << utils::AppConfig::Instance().server.host
		<< "\n\t   Port: " << utils::AppConfig::Instance().server.port
		<< "\n\tThreads: " << utils::AppConfig::Instance().server.threads;
}


void ServerApp::InitLogger()
{
	uint8_t severities{ 0 };

	if (utils::AppConfig::Instance().logger.enableDebug) {
		severities |= lg::Severity::debug;
	}
	if (utils::AppConfig::Instance().logger.enableError) {
		severities |= lg::Severity::error;
	}
	if (utils::AppConfig::Instance().logger.enableInfo) {
		severities |= lg::Severity::info;
	}
	if (utils::AppConfig::Instance().logger.enableWarning) {
		severities |= lg::Severity::warning;
	}
	
	lg::Logger::Instance().setLoggedSeverities(severities);

	const auto path = utils::AppConfig::Instance().logger.logFilePath;

	if (!path.empty()) {
		lg::Logger::Instance().setGlobalLogFile(path);
	}
}


int ServerApp::Run()
{
	return bs::Server{
		utils::AppConfig::Instance().server.host,
		utils::AppConfig::Instance().server.port,
		utils::AppConfig::Instance().server.threads
	}.Run();
}


}	// namespace app