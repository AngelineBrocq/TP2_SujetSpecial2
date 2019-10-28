#pragma once

#include <iostream>
#include <uvw.hpp>

class Client
{
public:
    Client(std::string p_IPAddress, int p_Port);
	void Client::connect(uvw::Loop& p_Loop);

private:
	std::string m_IPAddress;
	int m_Port;
	std::shared_ptr<uvw::Loop> loop;
};