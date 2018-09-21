#pragma once

#include "https/Types.hpp"

namespace https
{

class RequestHandler
{
public:
	Response HandleRquest(Request&& req);
};

}	// namespace https1