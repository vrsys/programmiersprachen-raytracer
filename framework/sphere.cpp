#include "sphere.hpp"
#include <numbers>

Sphere::Sphere(glm::vec3 const& center, float radius):
	Shape::Shape{},
	center_{center},
	radius_{radius} {}

float Sphere::area() const {
	return 4 * std::numbers::pi * radius_ * radius_ ;
}

float Sphere::volume() const {
	return (4.0f / 3.0f) * std::numbers::pi * radius_ * radius_ * radius_;
}