#pragma once

#include <glm/vec3.hpp>
#include <string>
#include "Color.hpp"

struct Light {
	float intensity = 1.0f;
	Color color = { 0.0f, 1.0f, 0.0f };
	glm::vec3 position = glm::vec3{ 0.0f, 0.0f, 0.0f };
};