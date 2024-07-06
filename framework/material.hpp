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

inline std::ostream& operator<<(std::ostream& os, Material const& material) // inline makes it so that the function can be defined within the header file
{
	os << "material name: " << material.name_ << " ka: " << "(" << material.ka_.r << ", " << material.ka_.g << ", " << material.ka_.b << ") "
		<< "kd: " << "(" << material.kd_.r << ", " << material.kd_.g << ", " << material.kd_.b << ") "
		<< "ks: " << "(" << material.ks_.r << ", " << material.kd_.g << ", " << material.kd_.b << ")";
	return os;
}
#endif