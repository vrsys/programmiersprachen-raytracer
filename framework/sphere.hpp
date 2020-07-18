#include <glm/vec3.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "shape.hpp"

class Sphere : public Shape {
	glm::vec3 center_;
	float radius_;
public:
	Sphere(glm::vec3 center, float radius);
	float area() override;
	float volume() override;
};