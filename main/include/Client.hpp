#pragma once

#include <iostream>
#include <uvw.hpp>

class Client
{
    Client(std::string p_IPAddress, int p_Port, uvw::Loop &p_Loop);
};