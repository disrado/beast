#pragma once

#include "server/Types.hpp"
#include "server/handlers/BaseRequestHandler.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <string_view>
#include <unordered_map>


namespace bs
{


class Router
{
public:
	static Router& Instance();

	std::unique_ptr<BaseRequestHandler> GerHandler(std::string_view route);
};


}	// namespace bs