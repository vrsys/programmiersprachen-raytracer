#pragma once
#include <string>
#include "color.hpp"

struct Material {
	std::string name = "no name";
	Color ka = { 0,0,0 };
	Color kd = { 0,0,0 };
	Color ks = { 0,0,0 };
	float m = 0.0f;
};

std::ostream& operator<<(std::ostream& os, Material const& m) {
	os << m.name << ":"  << "Ka:" << m.ka << ", " << "Kd:" << m.kd << ", " << "Ka:" << m.ks << ", " << m.m;
	return os;
}

