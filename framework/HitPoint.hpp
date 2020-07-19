#include <iostream>
#include <glm/vec3.hpp>

struct HitPoint {
	bool hashit = false;
	float distance = 0;
	std::string name = "";
	std::string color = "";
	glm::vec3 intersection = { 0.0f, 0.0f, 0.0f };
	glm::vec3 direction = { 0.0f, 0.0f, 0.0f };
};