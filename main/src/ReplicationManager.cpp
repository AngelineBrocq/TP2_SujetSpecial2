#include "ReplicationManager.hpp"

void ReplicationManager::Replicate(MemoryStream p_MemoryStream)
{

}

void ReplicationManager::Replicate(MemoryStream p_MemoryStream, std::vector<GameObject*> p_GameObjects)
{
	p_MemoryStream.Write(m_ProtocolID);
}