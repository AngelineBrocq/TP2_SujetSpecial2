#include "Player.hpp"

void Player::Write(OutputStream& p_Out) {
	p_Out.Write(m_PositionX);
	p_Out.Write(m_PositionY);
	p_Out.Write(m_PositionZ);

	p_Out.Write(m_Name, 128);

	p_Out.Write(m_RotationX);
	p_Out.Write(m_RotationY);
	p_Out.Write(m_RotationZ);
	p_Out.Write(m_RotationW);
}

void Player::Read(InputStream& p_In) {
	m_PositionX = p_In.Read<float>();
	m_PositionY = p_In.Read<float>();
	m_PositionZ = p_In.Read<float>();

	auto l_Name = p_In.Read(128);

	m_RotationX = p_In.Read<float>();
	m_RotationY = p_In.Read<float>();
	m_RotationZ = p_In.Read<float>();
	m_RotationW = p_In.Read<float>();

	std::copy(reinterpret_cast<char*>(l_Name.data()), reinterpret_cast<char*>(l_Name.data()) + l_Name.size_bytes(), m_Name);
}