#pragma once

#include <logger/Logger.hpp>

#include <boost/exception/all.hpp>

#include <string_view>
#include <iostream>


template<typename exceptionType>
void ThrowError(const std::string& message)
{
	BOOST_THROW_EXCEPTION(exceptionType(message));
}


template<typename exceptionType>
void LogAndThrow(const std::string& message)
{
	logger::LOG(logger::Severity::error) << message;
	ThrowError<exceptionType>(message);
}