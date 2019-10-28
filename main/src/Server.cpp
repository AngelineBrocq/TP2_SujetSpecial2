#include "Server.hpp"


Server::Server(std::string p_IPAddress, int p_Port, uvw::Loop &p_Loop)
{
	std::shared_ptr<uvw::TCPHandle> l_Tcp = p_Loop.resource<uvw::TCPHandle>();

	l_Tcp->once<uvw::ListenEvent>([](const uvw::ListenEvent&, uvw::TCPHandle& l_Server) {
		std::shared_ptr<uvw::TCPHandle> l_Client = l_Server.loop().resource<uvw::TCPHandle>();

		l_Client->on<uvw::CloseEvent>([ptr = l_Server.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { ptr->close(); });
		l_Client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle& l_Client) { l_Client.close(); });

		l_Server.accept(*l_Client);
		l_Client->read();
		m_ClientsList.push_back(l_Client);
		});

	l_Tcp->bind(p_IPAddress, p_Port);
	l_Tcp->listen();
}

void Server::Send(uint8_t *p_Packet, int p_Size)
{
	std::cout << "Sending data to all clients" << std::endl;
	std::for_each(m_ClientsList.begin(), m_ClientsList.end(), [p_Packet, p_Size](auto l_Client) {
		l_Client->write(reinterpret_cast<char*>(p_Packet), p_Size); 
	});
}