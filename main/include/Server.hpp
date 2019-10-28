#pragma once

#include <iostream>
#include <uvw.hpp>
#include <vector>
#include <thread>


class Server
{
public:
    Server(std::string p_IPAddress, int p_Port);
    ~Server();
	void listenServer(uvw::Loop& p_Loop);
    void Send(uint8_t *p_Packet, int p_Size);
	void Server::Run();

private:
	std::string m_IPAddress;
	int m_Port;
	std::shared_ptr<uvw::Loop> loop;
	std::unique_ptr<std::thread> loopThread;
	std::vector<std::shared_ptr<uvw::TCPHandle>> m_ClientsList;
	void runner();
};