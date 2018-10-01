#include "utils/Config.hpp"
#include "utils/Exception.hpp"

#include <fstream>


namespace utils
{


AppConfig& AppConfig::Instance()
{
	static AppConfig instance;
	return instance;
}


void AppConfig::ReadConfig(const std::filesystem::path& path)
{
	std::ifstream ifs{ path };

	if (!ifs.is_open()) {
		Throw<std::logic_error>(path.string());
	}

	nl::json jsonCfg;

	ifs >> jsonCfg;

	server = jsonCfg["server"].get<ServerConfig>();
	logger = jsonCfg["logger"].get<LoggerConfig>();
}


void from_json(const nl::json& j, ServerConfig& c)
{
	c.host = j.at("host").get<std::string>();
	c.port = j.at("port").get<uint16_t>();
	c.threads = j.at("threads").get<int>();
}


void to_json(nl::json& j, const ServerConfig& c)
{
	j = nl::json{
		{ "host", c.host },
		{ "port", c.port },
		{ "threads", c.threads }
	};
}

void from_json(const nl::json& j, LoggerConfig& c)
{
	c.enableDebug = j.at("enableDebug").get<bool>();
	c.enableError = j.at("enableError").get<bool>();
	c.enableInfo = j.at("enableInfo").get<bool>();
	c.enableWarning = j.at("enableWarning").get<bool>();
	c.logFilePath = j.at("logFilePath").get<std::string>();
}

void to_json(nl::json& j, const LoggerConfig& c)
{
	j = nl::json{
		{ "enableDebug", c.enableDebug },
		{ "enableError", c.enableError },
		{ "enableInfo", c.enableInfo },
		{ "enableWarning", c.enableWarning },
		{ "logFilePath", c.logFilePath }
	};
}


}	// namespace utils