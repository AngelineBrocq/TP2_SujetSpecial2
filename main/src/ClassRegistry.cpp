#include "ClassRegistry.hpp"

GameObject* ClassRegistry::Create(ReplicationClassID p_ClassID)
{
	auto l_Iterator = m_LinkIDClassToMethod.find(p_ClassID);
	if (l_Iterator!= m_LinkIDClassToMethod.end())
		return m_LinkIDClassToMethod.find(p_ClassID)->second();

	return nullptr;
}