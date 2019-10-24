#include "ReplicationManager.hpp"

void ReplicationManager::Replicate(MemoryStream p_MemoryStream)
{
	
}

void ReplicationManager::Replicate(MemoryStream p_MemoryStream, std::vector<GameObject*> p_GameObjects)
{
	for (int i = 0; i < p_GameObjects.size(); i++)
	{
		p_MemoryStream.Write(m_ProtocolID);
		p_MemoryStream.Write(m_PaquetID);
		p_MemoryStream.Write();//Idetntifiant classe
		p_MemoryStream.Write();//Identifiant gameobject
		p_MemoryStream.Write(p_GameObjects[i]);
	}
}