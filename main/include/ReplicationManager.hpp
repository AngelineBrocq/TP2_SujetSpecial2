#pragma once
#include <unordered_set>
#include "game_object.hpp"
#include <vector>

class ReplicationManager
{
private:
	std::unordered_set<GameObject*> m_AllGameObjects;
	uint32_t m_ProtocolID = 210626;

public:
	void Replicate(MemoryStream p_MemoryStream, std::vector<GameObject*> p_GameObjects);
	void Replicate(MemoryStream p_MemoryStream);
};
