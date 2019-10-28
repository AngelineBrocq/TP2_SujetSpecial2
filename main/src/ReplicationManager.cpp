#include "ReplicationManager.hpp"
#include "ClassRegistry.hpp"
#include "LinkingContext.hpp"
#include <optional>

ReplicationManager* ReplicationManager::m_Instance = new ReplicationManager;

void ReplicationManager::Replicate(InputStream p_MemoryStream)
{
	ClassRegistry* l_Registry = ClassRegistry::Get();
	LinkingContext* l_Context = LinkingContext::Get();
	std::unordered_set<GameObject*> l_ReplicationFlux;

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
			l_GameObject.value()->Read(p_MemoryStream);
			l_Context->AddIDAndGameObject(l_ClassID, l_GameObject.value());
			l_ReplicationFlux.insert(l_GameObject.value());
		}
		else
		{
			l_GameObject.value()->Read(p_MemoryStream);
			l_ReplicationFlux.insert(l_GameObject.value());
		}
	}
	
	/*for (std::vector<GameObject*>::iterator l_Ite = l_ReplicationFlux; l_Ite != l_ReplicationFlux.end(); l_Ite++)
	{
		if (!m_AllGameObjects.find(l_Ite))
		{
			l_Context->DeleteGameObject(l_Ite);
		}
	}*/

	/*for each (GameObject* l_GameObjToRemove in l_ReplicationFlux)
	{
		if (!m_AllGameObjects.find(l_GameObjToRemove.value()))
		{
			l_Context->DeleteGameObject(l_GameObjToRemove.value());
		}
	}*/

	std::for_each(l_ReplicationFlux.begin(), l_ReplicationFlux.end(), [this,l_Context](auto l_GameObjToRemove) {
		
		if (m_AllGameObjects.find(l_GameObjToRemove) != m_AllGameObjects.end())
		{
			l_Context->DeleteGameObject(l_GameObjToRemove);
		}
		});

	m_AllGameObjects.clear();
	m_AllGameObjects = l_ReplicationFlux;
	l_ReplicationFlux.clear();
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