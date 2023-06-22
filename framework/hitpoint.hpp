#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#ifndef HITPOINT_HPP
#define HITPOINT_HPP

struct HitPoint
{
	bool cut = false;
	float distance = 0.0f;
	std::string name = "";
	Color color = { 0.0, 0.0, 0.0 };
	glm::vec3 point = { 0.0f, 0.0f, 0.0 };
	glm::vec3 direction = { 0.0, 0.0, 0.0 };
};


#endif