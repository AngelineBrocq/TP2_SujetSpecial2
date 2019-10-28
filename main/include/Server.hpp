#pragma once

#include <iostream>
#include <uvw.hpp>
#include <vector>
#include "Client.hpp"

class Server
{
private:
    std::vector<std::shared_ptr<uvw::TCPHandle>> m_ClientsList;
public:
    Server(std::string p_IPAddress, int p_Port, uvw::Loop &p_Loop);
    void Send(uint8_t *p_Packet, int p_Size);
};