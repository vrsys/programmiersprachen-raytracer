#include "sphere.hpp"
#include "hitpoint.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <numbers>
#include <cmath>
#include <string>

Sphere::Sphere(std::string const& name_parameter, glm::vec3 const& color_parameter, glm::vec3 const& center_parameter, double radius_parameter) : Shape::Shape{ name_parameter, color_parameter }, center_{center_parameter}, radius_(radius_parameter)
{}

double Sphere::area() const {
	return 4 * std::numbers::pi * radius_ * radius_;
}

double Sphere::volume() const {
	return 4.0 / 3.0 * std::numbers::pi * radius_ * radius_ * radius_;
}

std::ostream& Sphere::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "center: (" << center_.x << ", " << center_.y << ", " << center_.z << ')' << " radius: " << radius_ << '\n';
}

HitPoint Sphere::intersect(Ray & ray_, float intersection_distance_parameter) const
{	
	ray_.direction = glm::normalize(ray_.direction);
	bool did_intersect_parameter = glm::intersectRaySphere(ray_.origin, ray_.direction, center_, radius_ * radius_, intersection_distance_parameter); // outside so intersection_distance_parameter is updated
	return HitPoint{ did_intersect_parameter, intersection_distance_parameter, Shape::name_, Shape::color_,  (ray_.origin + intersection_distance_parameter * ray_.direction), ray_.direction };
}

std::ostream& operator<<(std::ostream& os, Sphere const& s)
{
	return s.print(os);
}