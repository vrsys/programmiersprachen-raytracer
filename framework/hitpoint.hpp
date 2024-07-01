#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include "color.hpp"
#include <string>
#include <glm/vec3.hpp>

struct HitPoint
{
	bool did_intersect_{};
	float distance_{};
	std::string object_name_{};
	Color object_color_{};
	glm::vec3 position_{};
	glm::vec3 direction_{};
};

#endif