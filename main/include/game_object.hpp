#pragma once

#include <cstdint>
#include "streams.hpp"

using ReplicationClassID = uint32_t;

#define REPLICATED(id,className)                                    \
enum : ReplicationClassID{mClassID = id};                           \
virtual ReplicationClassID ClassID() const  { return mClassID;}     \
static GameObject* CreateInstance() {return new className();}       \

class GameObject
{
public:
	REPLICATED(3265, GameObject);
	virtual void Destroy();
	virtual void Write(OutputStream& p_Out);
	virtual void Read(InputStream& p_In);

};