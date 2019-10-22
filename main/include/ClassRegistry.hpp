#pragma once
#include <map>
#include <game_object.hpp>

class ClassRegistry
{
private:
	std::map<ReplicationClassID, std::function<GameObject *>> m_LinkIDClassToMethod;

	//Pour que ce soit un singleton
	static ClassRegistry* m_Instance;

public:

	template <class T>
	void AddClass(ReplicationClassID p_ClassID, std::function<GameObject*> p_Function)
	{
		m_LinkIDClassToMethod.insert(std::pair<ReplicationClassID, std::function<T::mClassID>>(p_ClassID, p_Function));
	}

	GameObject* Create(ReplicationClassID);

	//Pour que ce soit un singleton
	static ClassRegistry* Get()
	{
		if (!m_Instance)
			m_Instance = new ClassRegistry();
		return m_Instance;
	}

};
