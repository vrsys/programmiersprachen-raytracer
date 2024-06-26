#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <iostream>
#include "color.hpp"
#include <glm/vec3.hpp>

struct HitPoint {
	bool success;
	float distance;
	std::string name_intersected_obj;
	Color color_intersected_onj;
	glm::vec3 intersection_point;
	glm::vec3 ray_direction;
};

#endif