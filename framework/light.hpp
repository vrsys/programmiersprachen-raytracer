#include <glm/vec3.hpp>
#include "color.hpp"

struct Light
{
	Light();
	Light(std::string name, glm::vec3 pos, Color color, float brightness);

	std::string name_;
	glm::vec3 pos_;
	Color color_;
	float brightness_;
};

