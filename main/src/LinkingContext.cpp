#include "LinkingContext.hpp"

void LinkingContext::AddIDAndGameObject(int p_NetID, GameObject* p_GameObject)
{
	m_LinkGameObjectToID.insert(std::pair<GameObject*, int>(p_GameObject, p_NetID));
	m_LinkIDToGameObject.insert(std::pair<int, GameObject*>(p_NetID, p_GameObject));
}

void LinkingContext::AddGameObject(GameObject* p_GameObject)
{
	
}

void LinkingContext::DeleteGameObject(GameObject* p_GameObject) 
{

}

std::optional<GameObject*> LinkingContext::GetGameObject(int p_NetId) 
{

}

std::optional<int> LinkingContext::GetID(GameObject* p_GameObject)
{

}