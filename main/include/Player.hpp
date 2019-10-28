#pragma once
#include "game_object.hpp"
#include <iostream>

class Player : public GameObject
{
private:
	float m_PositionX;
	float m_PositionY;
	float m_PositionZ;

	//char m_Name[128];
	std::string m_Name;

	float m_RotationX;
	float m_RotationY;
	float m_RotationZ;
	float m_RotationW;

public:
	REPLICATED(2586, Player);
	void Write(OutputStream& p_Out);
	void Read(InputStream& p_In);
	void Print();
	Player(float p_PosX, float p_PosY, float p_PosZ, std::string p_Name, float p_RotX, float p_RotY, float p_RotZ, float p_RotW);
	Player() {};
};
