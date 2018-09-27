#pragma once 

#include <nlohmann/json.hpp>

#include <filesystem>
#include <string>


namespace utils
{


namespace nl = nlohmann;


struct ServerConfig
{
	std::string host;
	uint16_t port;
	int threads;
};


class AppConfig
{
public:
	static AppConfig& Instance();

	void ReadConfig(const std::filesystem::path& path);

public:
	ServerConfig server;
};


void from_json(const nl::json& j, ServerConfig& c);
void to_json(nl::json& j, const ServerConfig& c);


}	// namespace utils