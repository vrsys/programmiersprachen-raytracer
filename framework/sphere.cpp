#include "sphere.hpp"
#include <numbers>
#include "glm/gtx/intersect.hpp"

Sphere::Sphere(std::string name, Color color, glm::vec3 const& center, float radius):
	Shape::Shape{name, color},
	center_{center},
	radius_{radius} {}

float Sphere::area() const {
	return 4 * std::numbers::pi * radius_ * radius_ ;
}

float Sphere::volume() const {
	return (4.0f / 3.0f) * std::numbers::pi * radius_ * radius_ * radius_;
}

std::ostream& Sphere::print(std::ostream& os) const {
	return Shape::print(os) <<
		"Radius: " << radius_ << "\n" <<
		"Center: " << "(" << center_.x << ", " << center_.y << ", " << center_.z << ")\n";
}