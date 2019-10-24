#include "ReplicationManager.hpp"
#include "ClassRegistry.hpp"
#include "LinkingContext.hpp"

void ReplicationManager::Replicate(InputStream p_MemoryStream)
{

}

void ReplicationManager::Replicate(OutputStream p_MemoryStream, std::vector<GameObject*> p_GameObjects)
{
	ClassRegistry* l_Registry = ClassRegistry::Get();
	for (int i = 0; i < p_GameObjects.size(); i++)
	{
		uint32_t l_ClassID = l_Registry->AddClass<GameObject>();
		p_MemoryStream.Write(m_ProtocolID);
		p_MemoryStream.Write(m_PacketID);
		p_MemoryStream.Write(l_ClassID);//Identifiant classe

		LinkingContext* l_Context = LinkingContext::Get();
		std::optional<NetworkID> l_NetID = l_Context->GetID(p_GameObjects[i]);
		p_MemoryStream.Write(l_NetID);//Identifiant gameobject

		p_GameObjects[i]->Write(p_MemoryStream);
		m_PacketID++;
	}
}