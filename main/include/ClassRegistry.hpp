#pragma once
#include <map>
#include <game_object.hpp>

class ClassRegistry
{
private:
	std::map<ReplicationClassID, std::function<GameObject*()>> m_LinkIDClassToMethod;

	//Pour que ce soit un singleton
	static ClassRegistry* m_Instance;

public:

	template <class T>
	ReplicationClassID AddClass()
	{
		m_LinkIDClassToMethod.insert(std::pair<ReplicationClassID, std::function<GameObject*()>>(T::mClassID, new T));
		return T::mClassID;
	}

	GameObject* Create(ReplicationClassID p_ClassId);

	//Pour que ce soit un singleton
	static ClassRegistry* Get()
	{
		if (!m_Instance)
			m_Instance = new ClassRegistry();
		return m_Instance;
	}

};
