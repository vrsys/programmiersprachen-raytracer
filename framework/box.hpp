#define GLM_SWIZZLE
#include <glm/vec3.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "shape.hpp"

class Box : public Shape {
	glm::vec3 min_;
	glm::vec3 max_;
public:
	Box(glm::vec3 min, glm::vec3 max, std::string name, std::string color);
	float area() override;
	float volume() override;

};