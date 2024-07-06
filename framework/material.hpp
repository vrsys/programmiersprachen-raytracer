#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <string>

struct Material
{
	std::string name_{ "placeholder" };
	Color ka_{ 0, 0, 0 };
	Color kd_{ 0, 0, 0 };
	Color ks_{ 0, 0, 0 };
	float exponent_{ 0 };
};

#endif