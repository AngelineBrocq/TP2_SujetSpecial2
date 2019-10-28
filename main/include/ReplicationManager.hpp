#pragma once
#include <unordered_set>
#include "game_object.hpp"
#include <vector>

class ReplicationManager
{
private:
	std::unordered_set<GameObject*> m_AllGameObjects;
	uint32_t m_ProtocolID = 211226;
	uint32_t m_PacketID = 0;
	static ReplicationManager* m_Instance;

public:
	void Replicate(OutputStream p_MemoryStream, std::vector<GameObject*> p_GameObjects);
	void Replicate(InputStream p_MemoryStream);
	std::unordered_set<GameObject*> GetAllGameObjects();

	static ReplicationManager* Get()
	{
		if (!m_Instance)
			m_Instance = new ReplicationManager();
		return m_Instance;
	}
};
