#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "color.hpp"
#include "glm/vec3.hpp"

#include <string>

struct Light
{
	std::string name_;
	glm::vec3 position_;
	Color color_; //max should be 1.0
	int brightness_;
};

#endif
