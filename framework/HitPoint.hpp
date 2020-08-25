
#ifndef HIT_POINT_HPP_
#define HIT_POINT_HPP_


#include <iostream>
#include <glm/vec3.hpp>
#include <color.hpp>

struct HitPoint {
	bool hashit = false;
	float distance = 0;
	std::string name = "";
	Color color = { 0.0f, 0.0f, 0.0f };
	glm::vec3 intersection = { 0.0f, 0.0f, 0.0f };
	glm::vec3 direction = { 0.0f, 0.0f, 0.0f };
};

#endif