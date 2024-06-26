#include "box.hpp"
#include <glm/vec3.hpp>
#include <cmath>

Box::Box(glm::vec3 const& maximum_parameter, glm::vec3 const& minimum_parameter) : Shape::Shape{}, maximum_(maximum_parameter), minimum_(minimum_parameter)
{}

double Box::area() const {
	double a = std::abs(maximum_.x - minimum_.x);
	double b = std::abs(maximum_.y - minimum_.y);
	double c = std::abs(maximum_.z - minimum_.z);
	return 2 * (a * (b + c) + b * c);
}

double Box::volume() const {
	glm::vec3 diagonal_{ maximum_ - minimum_ };
	return std::abs(diagonal_.x * diagonal_.y * diagonal_.z);
}
