#include <glm/vec3.hpp>
#include "shape.hpp"
#include "Box.hpp"
#include "color.hpp"
#include <string>

#define OWN_PI 3.14159265359

Box::Box(glm::vec3 const& min, glm::vec3 const& max) : Shape{}, min_{ min }, max_{ max } {};

Box::Box(std::string const& name, glm::vec3 const& min, glm::vec3 const& max, Color const& color) : Shape{name,color}, min_{ min }, max_{ max } {};

float Box::area() const{
	glm::vec3 quad = max_ - min_;
	float area = 2 *(abs(quad.x * quad.y) + abs(quad.x * quad.z) + abs(quad.y * quad.z));
	return area;
}

float Box::volume() const{
	glm::vec3 quad = max_ - min_;
	return abs(quad.x * quad.y * quad.z);
}

std::ostream& Box::print(std::ostream& os)const {
	Shape::print(os);
	os << "Minimum: " << "{" << min_.r << "; " << min_.g << "; " << min_.b << "};" << "Maximum: " << "{" << max_.r << "; " << max_.g << "; " << max_.b << "};";
	return os;
}