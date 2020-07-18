#include "glm/ext.hpp"
#include "sphere.hpp"

Sphere::Sphere(glm::vec3& center, float radius, std::string name, std::string color) : Shape(name, color)
{
	center_ = center;
	radius_ = radius;
}

float Sphere::area()
{
	return 4* M_PI* radius_* radius_;
}

float Sphere::volume()
{
	return (4/3)*M_PI*pow(radius_,3);
}

std::ostream& Sphere::print(std::ostream& os) const
{
	Shape::print(os);
	os << "Center: " << glm::to_string(center_) << " Radius: " << radius_;
	return os;
}
