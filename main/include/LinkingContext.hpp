#pragma once
#include "game_object.hpp"
#include <map>
#include <optional>

using NetworkID = uint64_t;

class LinkingContext
{
private:
	std::map<NetworkID, GameObject*> m_LinkIDToGameObject;
	std::map<GameObject*, NetworkID> m_LinkGameObjectToID;

public:
	LinkingContext();
	void AddIDAndGameObject(NetworkID p_NetID, GameObject* p_GameObject);
	void DeleteGameObject(GameObject* p_GameObject);
	void AddGameObject(GameObject* p_GameObject);

	std::optional<NetworkID> GetID(GameObject* p_GameObject);
	std::optional<GameObject*> GetGameObject(NetworkID p_NetID);

	NetworkID GetLastID();
	
};
