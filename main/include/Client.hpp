#pragma once
#include <uvw.hpp>
#include <thread>
#include <iostream>
#include "ReplicationManager.hpp"
#include "ClassRegistry.hpp"
#include "game_object.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "streams.hpp"

class Client
{
public:
    Client(std::string p_IPAddress, int p_Port);
	~Client();
	void connect(uvw::Loop& p_Loop);

private:
	std::string m_IPAddress;
	int m_Port;
	std::shared_ptr<uvw::Loop> m_Loop;
	std::unique_ptr<std::thread> m_LoopThread;
	void Runner();
};