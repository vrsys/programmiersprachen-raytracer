//#pragma once

#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <string>
#include "color.hpp"

struct Material {
	std::string name = "no name";
	Color ka = { 0,0,0 };
	Color kd = { 0,0,0 };
	Color ks = { 0,0,0 };
	float m = 0.0f;
};

std::ostream& operator<<(std::ostream& os, Material const& m);


#endif
