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

public:
	void Replicate(OutputStream p_MemoryStream, std::vector<GameObject*> p_GameObjects);
	void Replicate(InputStream p_MemoryStream);
};
