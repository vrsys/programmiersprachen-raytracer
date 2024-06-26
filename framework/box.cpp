#include "box.hpp"
#include <glm/vec3.hpp>
#include <cmath>

Box::Box(std::string const& name_parameter, glm::vec3 const& color_parameter, glm::vec3 const& maximum_parameter, glm::vec3 const& minimum_parameter) : Shape::Shape{ name_parameter, color_parameter }, maximum_(maximum_parameter), minimum_(minimum_parameter)
{}

double Box::area() const {
	glm::vec3 diagonal_{ maximum_ - minimum_ };
	double a = std::abs(diagonal_.x);
	double b = std::abs(diagonal_.y);
	double c = std::abs(diagonal_.z);
	return 2 * (a * (b + c) + b * c);
}

double Box::volume() const {
	glm::vec3 diagonal_{ maximum_ - minimum_ };
	return std::abs(diagonal_.x * diagonal_.y * diagonal_.z);
}
