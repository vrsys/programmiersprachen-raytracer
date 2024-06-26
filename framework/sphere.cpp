#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <numbers>
#include <cmath>

Sphere::Sphere(std::string const& name_parameter, glm::vec3 const& color_parameter, glm::vec3 const& center_parameter, double radius_parameter) : Shape::Shape{ name_parameter, color_parameter }, center_{center_parameter}, radius_(radius_parameter)
{}

double Sphere::area() const {
	return 4 * std::numbers::pi * radius_ * radius_;
}

double Sphere::volume() const {
	return 4.0 / 3.0 * std::numbers::pi * radius_ * radius_ * radius_;
}