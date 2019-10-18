#include "LinkingContext.hpp"

void LinkingContext::AddIDAndGameObject(NetworkID p_NetID, GameObject* p_GameObject)
{
	auto l_Iterator = m_LinkGameObjectToID.find(p_GameObject);
	if (l_Iterator != m_LinkGameObjectToID.end())
	{
		return;
	}
	m_LinkGameObjectToID.insert(std::pair<GameObject*, NetworkID>(p_GameObject, p_NetID));
	m_LinkIDToGameObject.insert(std::pair<NetworkID, GameObject*>(p_NetID, p_GameObject));
}

void LinkingContext::AddGameObject(GameObject* p_GameObject)
{
	auto l_Iterator = m_LinkGameObjectToID.find(p_GameObject);
	if (l_Iterator != m_LinkGameObjectToID.end())
	{
		return;
	}
	
	NetworkID l_NextID = GetLastID() + 1;
	m_LinkGameObjectToID.insert(std::pair<GameObject*, NetworkID>(p_GameObject, l_NextID));
	m_LinkIDToGameObject.insert(std::pair<NetworkID, GameObject*>(l_NextID, p_GameObject));
}

void LinkingContext::DeleteGameObject(GameObject* p_GameObject) 
{
	auto l_Iterator = m_LinkGameObjectToID.find(p_GameObject);
	if (l_Iterator != m_LinkGameObjectToID.end())
	{
		m_LinkGameObjectToID.erase(l_Iterator);
		m_LinkIDToGameObject.erase(l_Iterator->second);
	}
}

std::optional<GameObject*> LinkingContext::GetGameObject(NetworkID p_NetId) 
{
	return m_LinkIDToGameObject.find(p_NetId)->second;
}

std::optional<NetworkID> LinkingContext::GetID(GameObject* p_GameObject)
{
	return m_LinkGameObjectToID.find(p_GameObject)->second;
}

NetworkID LinkingContext::GetLastID()
{
	if (!m_LinkIDToGameObject.empty())
		return m_LinkIDToGameObject.rbegin()->first;
	return 1;
}