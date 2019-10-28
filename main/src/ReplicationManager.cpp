#include "ReplicationManager.hpp"
#include "ClassRegistry.hpp"
#include "LinkingContext.hpp"
#include <optional>

ReplicationManager* ReplicationManager::m_Instance = new ReplicationManager;

void ReplicationManager::Replicate(InputStream p_MemoryStream)
{
	ClassRegistry* l_Registry = ClassRegistry::Get();
	LinkingContext* l_Context = LinkingContext::Get();

	if (p_MemoryStream.Read<uint32_t>() != m_ProtocolID)
		return;

	p_MemoryStream.Read<uint32_t>(); //Lecture du packet id a comparer

	while (ReplicationClassID l_ClassID = p_MemoryStream.Read<ReplicationClassID>())
	{
		NetworkID l_NetID = p_MemoryStream.Read<NetworkID>();
		std::optional<GameObject* > l_GameObject = l_Context->GetGameObject(l_NetID);
		if(l_GameObject == nullptr)
		{
			l_GameObject = l_Registry->Create(l_ClassID);
		}
		l_GameObject.value()->Read(p_MemoryStream);
	}
}

void ReplicationManager::Replicate(OutputStream p_MemoryStream, std::vector<GameObject*> p_GameObjects)
{
	ClassRegistry* l_Registry = ClassRegistry::Get();
	for (int i = 0; i < p_GameObjects.size(); i++)
	{
		ReplicationClassID l_ClassID = l_Registry->AddClass<GameObject>();
		p_MemoryStream.Write(m_ProtocolID);
		p_MemoryStream.Write(m_PacketID);
		p_MemoryStream.Write(l_ClassID);//Identifiant classe

		LinkingContext* l_Context = LinkingContext::Get();
		std::optional<NetworkID> l_NetID = l_Context->GetID(p_GameObjects[i]);
		p_MemoryStream.Write(l_NetID.value());//Identifiant gameobject

		p_GameObjects[i]->Write(p_MemoryStream);
		m_PacketID++;
	}
	p_MemoryStream.Flush();
}

std::unordered_set<GameObject*> ReplicationManager::GetAllGameObjects()
{
	return m_AllGameObjects;
}