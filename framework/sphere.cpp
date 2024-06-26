#include "sphere.hpp"
#include <numbers>
#include "glm/gtx/intersect.hpp"

Sphere::Sphere(std::string const& name, Color const& color, glm::vec3 const& center, float radius):
	Shape::Shape{name, color},
	center_{center},
	radius_{radius} {
	std::cout << "Sphere Konstruktor Aufruf" << std::endl;
}

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

HitPoint Sphere::intersect(Ray const& ray) const {
	HitPoint hit_point{ false, 0.0f, Shape::name_, Shape::color_, {0.0f, 0.0f, 0.0f}, ray.direction };
	hit_point.success = glm::intersectRaySphere(ray.origin, ray.direction, center_,
		radius_ * radius_, hit_point.distance);
	hit_point.intersection_point = ray.origin + hit_point.distance * ray.direction;
	return hit_point;
}

Sphere::~Sphere() {
	std::cout << "Sphere Destruktor Aufruf" << std::endl;
}