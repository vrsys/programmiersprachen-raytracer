#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
	Sphere(glm::vec3 const& center_parameter, double radius_parameter);
	double area() const override;
	double volume() const override;
private:
	glm::vec3 center_;
	double radius_;
};

#endif