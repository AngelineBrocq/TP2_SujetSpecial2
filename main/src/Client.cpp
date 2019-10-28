#include "Client.hpp"
#include "ReplicationManager.hpp"

Client::Client(std::string p_IPAddress, int p_Port)
{
	m_IPAddress = p_IPAddress;
	m_Port = p_Port;
	loop = uvw::Loop::getDefault();
	connect(*loop);
	loop->run();
}

void Client::connect(uvw::Loop& p_Loop)
{
	auto l_Tcp = p_Loop.resource<uvw::TCPHandle>();

	l_Tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent&, uvw::TCPHandle&) { /* handle errors */ });

	l_Tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent&, uvw::TCPHandle& l_Tcp) {
		auto l_DataWrite = std::unique_ptr<char[]>(new char[2]{ 'b', 'c' });
		l_Tcp.write(std::move(l_DataWrite), 2);
		l_Tcp.read();
		});

	l_Tcp->on<uvw::DataEvent>([](const uvw::DataEvent& l_Event, uvw::TCPHandle&) {
		
		std::string l_Result(l_Event.data.get(), l_Event.length);
		ReplicationManager* l_ReplicationManager = ReplicationManager::Get();

		InputStream l_Input(l_Result);
		l_ReplicationManager->Replicate(l_Input);
		
		std::unordered_set<GameObject*> l_AllGameObjects = l_ReplicationManager->GetAllGameObjects();
		for (auto l_GameObject : l_AllGameObjects)
		{
			l_GameObject->Print();
		}

		});

	l_Tcp->connect(m_IPAddress, m_Port);
}