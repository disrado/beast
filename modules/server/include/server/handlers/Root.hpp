#pragma once

#include "server/handlers/BaseRequestHandler.hpp"
#include "server/Types.hpp"


namespace bs
{


class Root : public BaseRequestHandler
{
public:
	virtual ResponseShPtr<> Handle(Request<>&& request) override;
};


}	// namespace bs