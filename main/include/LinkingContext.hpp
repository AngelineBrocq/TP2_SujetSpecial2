#pragma once
#include "game_object.hpp"
#include <map>
#include <optional>

class LinkingContext
{
private:
	std::map<int, GameObject*> m_LinkIDToGameObject;
	std::map<GameObject*, int> m_LinkGameObjectToID;

public:
	void AddIDAndGameObject(int p_NetID, GameObject* p_GameObject);
	void DeleteGameObject(GameObject* p_GameObject);
	void AddGameObject(GameObject* p_GameObject);

	std::optional<int> GetID(GameObject* p_GameObject);
	std::optional<GameObject*> GetGameObject(int p_NetID);
	
};
