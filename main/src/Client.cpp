#include "Client.hpp"

Client::Client(std::string p_IPAddress, int p_Port, uvw::Loop &p_Loop)
{
	auto l_Tcp = p_Loop.resource<uvw::TCPHandle>();

	l_Tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { /* handle errors */ });

	l_Tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent&, uvw::TCPHandle& l_Tcp) {
		auto l_DataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
		l_Tcp.write(std::move(l_DataWrite), 2);
		l_Tcp.close();
		});

	l_Tcp->on<uvw::DataEvent>([](const uvw::DataEvent& l_Event, uvw::TCPHandle&) {
		std::cout << l_Event.data.get() << std::endl;
		});

	l_Tcp->connect(p_IPAddress, p_Port);
}