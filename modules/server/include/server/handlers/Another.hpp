#pragma once

#include "server/handlers/BaseRequestHandler.hpp"


namespace bs
{


class Another : public BaseRequestHandler
{
public:
	virtual ResponseShPtr<> Handle(Request<>&& request) override;
};


}	// namespace bs