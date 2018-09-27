#include "utils/AppConfig.hpp"
#include "utils/Exception.hpp"

#include <fstream>

#include <iostream>


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
		LogAndThrow<std::logic_error>(path.string());
	}

	nl::json jsonCfg;

	ifs >> jsonCfg;

	server = jsonCfg["server"].get<ServerConfig>();
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


}	// namespace utils