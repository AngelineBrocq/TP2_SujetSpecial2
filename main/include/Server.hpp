#pragma once

#include <iostream>
#include <uvw.hpp>
#include <vector>
#include <thread>
#include "streams.hpp"
#include "ReplicationManager.hpp"


class Server
{
public:
    Server(std::string p_IPAddress, int p_Port);
    ~Server();
	void ListenServer(uvw::Loop& p_Loop);
    void Send(uint8_t *p_Packet, int p_Size);
	void Run();
	void PrepareAndSend(OutputStream& os, std::vector<GameObject*>& gameObjects);

private:
	std::string m_IPAddress;
	int m_Port;
	std::shared_ptr<uvw::Loop> m_Loop;
	std::unique_ptr<std::thread> m_LoopThread;
	std::vector<std::shared_ptr<uvw::TCPHandle>> m_ClientsList;
	void Runner();
};