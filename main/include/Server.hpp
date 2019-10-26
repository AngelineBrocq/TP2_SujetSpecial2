#pragma once

#include <iostream>
#include <uvw.hpp>
#include <vector>
#include "Client.hpp"

class Server
{
private:
    std::vector<Client*> m_ClientsList;
public:
    Server(std::string p_IPAddress, int p_Port, uvw::Loop &p_Loop);
};