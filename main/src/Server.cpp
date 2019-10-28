#include "Server.hpp"
#include "streams.hpp"
#include "game_object.hpp"
#include "Player.hpp"
#include "Enemy.hpp"


Server::Server(std::string p_IPAddress, int p_Port)
{
	m_IPAddress = p_IPAddress;
	m_Port = p_Port;
	m_Loop = uvw::Loop::getDefault();
	ListenServer(*m_Loop);
	m_LoopThread = std::make_unique<std::thread>(&Server::Runner, this);
}

Server::~Server()
{
	if (m_LoopThread->joinable()) {
		m_LoopThread->join();
	}
}

void Server::ListenServer(uvw::Loop& p_Loop) 
{
	std::shared_ptr<uvw::TCPHandle> l_Tcp = p_Loop.resource<uvw::TCPHandle>();

	l_Tcp->on<uvw::ListenEvent>([this](const uvw::ListenEvent&, uvw::TCPHandle& l_Server) {
		std::shared_ptr<uvw::TCPHandle> l_Client = l_Server.loop().resource<uvw::TCPHandle>();
		std::cout << "New connection" << std::endl;

		l_Client->on<uvw::CloseEvent>([ptr = l_Server.shared_from_this()](const uvw::CloseEvent&, uvw::TCPHandle&) { ptr->close(); });
		l_Client->on<uvw::EndEvent>([](const uvw::EndEvent&, uvw::TCPHandle& l_Client) { l_Client.close(); });

		l_Server.accept(*l_Client);
		l_Client->read();
		m_ClientsList.push_back(l_Client);
		});

	l_Tcp->bind(m_IPAddress, m_Port);
	l_Tcp->listen();
}

void Server::Send(uint8_t *p_Packet, int p_Size)
{
	std::cout << "Sending data to all clients" << std::endl;
	std::for_each(m_ClientsList.begin(), m_ClientsList.end(), [p_Packet, p_Size](auto l_Client) {
		l_Client->write(reinterpret_cast<char*>(p_Packet), p_Size); 
	});
}

void Server::Run()
{
	std::cout << "Server running" << std::endl;
	OutputStream l_Stream;

	std::vector<GameObject*> l_GameObjects;

	l_GameObjects.push_back(new Player(128, 002, 040, "Bidule", 256, 214,321,201));

	std::string command;
	std::cin >> command;
	if (command == "send") PrepareAndSend(l_Stream, l_GameObjects);
}

void Server::Runner() 
{
	m_Loop->run();
}





void Server::PrepareAndSend(OutputStream& os, std::vector<GameObject*>& gameObjects)
{
	os.Flush();
	ReplicationManager* replicationManager = ReplicationManager::Get();
	replicationManager->Replicate(os, gameObjects);

	auto data = os.Data();
	uint8_t* dataToSend = NULL;
	int dataSize = data.size();
	dataToSend = new uint8_t[dataSize];

	for (int i = 0; i < dataSize; i++)
	{
		dataToSend[i] = static_cast<uint8_t>(data[i]);
	}
	Send(dataToSend, dataSize);
	delete[] dataToSend;
	dataToSend = NULL;
}