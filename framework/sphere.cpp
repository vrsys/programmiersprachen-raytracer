
#include "sphere.hpp"

Sphere::Sphere(glm::vec3 center, float radius)
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
