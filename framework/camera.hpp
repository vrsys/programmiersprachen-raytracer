#pragma once

#include <glm/vec3.hpp>
#include <string>
#include "Color.hpp"

struct Camera {
	float intensity = 1.0f;
	glm::vec3 origin = glm::vec3{ 0.0f, 0.0f, 0.0f };
	float fov = 0.0f;
};