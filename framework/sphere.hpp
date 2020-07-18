#include <glm/vec3.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "shape.hpp"

class Sphere : public Shape {
	glm::vec3 center_;
	float radius_;
public:
	Sphere(glm::vec3 center, float radius, std::string name, std::string color);
	float area();
	float volume();
	std::ostream& print(std::ostream& os) const;
};