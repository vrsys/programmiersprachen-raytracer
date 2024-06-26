#include "box.hpp"
#include <numbers>

Box::Box(std::string const& name, Color const& color, glm::vec3 const& min, glm::vec3 const& max):
	Shape::Shape{name, color},
	min_{min},
	max_{max} {}

float Box::area() const {
	glm::vec3 diag = max_ - min_;
	return (diag.x * diag.y + diag.y * diag.z + diag.z * diag.x) * 2;
}

float Box::volume() const {
	glm::vec3 diag = max_ - min_;
	return diag.x * diag.y * diag.z;
}

std::ostream& Box::print(std::ostream& os) const {
	return Shape::print(os) <<
		"Min: " << "(" << min_.x << ", " << min_.y << ", " << min_.z << ")\n" <<
		"Max: " << "(" << max_.x << ", " << max_.y << ", " << max_.z << ")\n";
}