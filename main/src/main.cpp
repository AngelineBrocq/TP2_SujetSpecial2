#include <iostream>
#include <string_view>

#include <uvw.hpp>
#include <memory>
#include <Server.hpp>
#include <Client.hpp>

int main(int argc, char* argv[]) {

	std::string l_status = argv[1];
	std::string l_addr = argv[2];
	std::string l_portInput = argv[3];
	int port = atoi(l_portInput.c_str());

	if (l_status == "server") {
		auto srv = Server(l_addr, port);
		srv.Run();
	}
	else if (l_status == "client") {
		auto cl = Client(l_addr, port);
	}
	else {
		std::cout << "Write \"server\" for run server or \"client\" to run client" << std::endl;
	}

	return 0;
}