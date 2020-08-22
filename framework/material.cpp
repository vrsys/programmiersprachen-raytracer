#include "material.hpp"


Material::Material() :
	ka_{ 0.0f , 0.0f , 0.0f },
	kd_{ 0.0f , 0.0f , 0.0f },
	ks_{ 0.0f , 0.0f , 0.0f },
	m_{ 10.0f }{}


Material::Material( Color ka, Color kd, Color ks, float m):
	//name_{ name },
	ka_{ ka },
	kd_{ kd },
	ks_{ ks },
	m_{ m }{}
