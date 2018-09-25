#include <https/Server.hpp>

int main(int argc, char* argv[])
{
	if (argc != 4) {
		std::cerr
			<< "Usage: http-server-async <address> <port> <threads num>" << std::endl
			<< "Example:" << std::endl
			<< "    http-server-async 0.0.0.0 8080 1"  << std::endl;

		return EXIT_FAILURE;
	}

	const auto address{ boost::asio::ip::make_address(argv[1]) };
	const auto port{ static_cast<unsigned short>(std::atoi(argv[2])) };
	const auto threadsNum{ std::max<int>(1, std::atoi(argv[3])) };

	return https::Server{ address, port, threadsNum }.Run();
}