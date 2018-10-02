#pragma once

#include "server/Types.hpp"


namespace bs
{


class BaseRequestHandler
{
public:
	virtual ~BaseRequestHandler();

	virtual ResponseShPtr<> Handle(Request<>&& request) = 0;
};


}	// namespace bs