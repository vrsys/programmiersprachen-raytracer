#include "material.hpp"

Material::Material(std::string name, Color ka, Color kd, Color ks, float m):
	name_{ name },
	ka_{ ka },
	kd_{ kd },
	ks_{ ks },
	m_{ m }{}
