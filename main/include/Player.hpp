#pragma once
#include "game_object.hpp"
#include <iostream>

class Player : public GameObject
{
private:
	float m_PositionX;
	float m_PositionY;
	float m_PositionZ;

	char m_Name[128];

	float m_RotationX;
	float m_RotationY;
	float m_RotationZ;
	float m_RotationW;

public:
	void Write(OutputStream& p_Out);
	void Read(InputStream& p_In);
};
