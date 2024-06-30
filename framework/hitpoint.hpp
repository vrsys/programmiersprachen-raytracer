#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include "color.hpp"
#include <string>
#include <glm/vec3.hpp>

struct HitPoint
{
	HitPoint(bool did_intersect_parameter, float distance_parameter, std::string object_name_parameter, Color object_color_parameter, glm::vec3 position_parameter, glm::vec3 direction_parameter);
	bool did_intersect_;
	float distance_;
	std::string object_name_;
	Color object_color_;
	glm::vec3 position_;
	glm::vec3 direction_;
};

#endif