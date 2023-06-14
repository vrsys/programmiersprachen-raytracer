#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
	glm::vec3 min = { 0,0,0 };
	glm::vec3 max = { 0,0,0 };

};