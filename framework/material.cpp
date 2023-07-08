#include "material.hpp"



std::ostream& operator<<(std::ostream& os, Material const& m) {
	os << m.name << ":" << "Ka:" << m.ka << ", " << "Kd:" << m.kd << ", " << "Ka:" << m.ks << ", " << m.m;
	return os;
}