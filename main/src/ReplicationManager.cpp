#include "ReplicationManager.hpp"
#include "ClassRegistry.hpp"
#include "LinkingContext.hpp"

void ReplicationManager::Replicate(MemoryStream p_MemoryStream)
{
	
}

void ReplicationManager::Replicate(MemoryStream p_MemoryStream, std::vector<GameObject*> p_GameObjects)
{
	ClassRegistry* l_Registry = ClassRegistry::Get();
	for (int i = 0; i < p_GameObjects.size(); i++)
	{
		uint32_t l_ClassID = l_Registry->AddClass<GameObject>();
		p_MemoryStream.Write(m_ProtocolID);
		p_MemoryStream.Write(m_PaquetID);
		p_MemoryStream.Write(l_ClassID);//Idetntifiant classe

		//std::optional<NetworkID> l_NetID;
		//p_MemoryStream.Write();//Identifiant gameobject
		//p_GameObjects[i]->Write(p_MemoryStream);
	}
}