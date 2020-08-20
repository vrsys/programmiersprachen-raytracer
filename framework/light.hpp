#include <glm/vec3.hpp>
#include "color.hpp"

class Light
{
public:
	Light(std::string name, glm::vec3 pos, Color color, float brightness);

public:
	std::string name_;
	glm::vec3 pos_;
	Color color_;
	float brightness_;
};

