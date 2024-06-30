#include "hitpoint.hpp"
#include "color.hpp"
#include <string>

HitPoint::HitPoint(bool did_intersect_parameter, float distance_parameter, std::string object_name_parameter, Color object_color_parameter, glm::vec3 position_parameter, glm::vec3 direction_parameter) : 
	did_intersect_(did_intersect_parameter), 
	distance_(distance_parameter),
	object_name_(object_name_parameter),
	object_color_(object_color_parameter),
	position_(position_parameter),
	direction_(direction_parameter)
{}