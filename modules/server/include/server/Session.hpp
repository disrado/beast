#pragma once

#include <boost/beast/core.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <functional>
#include <iostream>
#include <memory>

#include "server/Types.hpp"


namespace bs
{


class Session : public std::enable_shared_from_this<Session>
{
private:
	using tcp = boost::asio::ip::tcp;

public:
	explicit Session(tcp::socket socket);

	void Run();

private:
	void OnRead(boost::system::error_code ec, std::size_t bytes_transferred);
	void OnWrite(boost::system::error_code ec, std::size_t bytes_transferred, bool close);
	void DoClose();

private:
	tcp::socket m_socket;
	boost::asio::strand<boost::asio::io_context::executor_type> m_strand;
	boost::beast::flat_buffer m_buffer;
	Request<> m_request;
	std::shared_ptr<void> m_response;
};


}	// namespace bs