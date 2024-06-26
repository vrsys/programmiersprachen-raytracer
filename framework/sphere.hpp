#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
	Sphere(std::string const& name_parameter, glm::vec3 const& color_parameter, glm::vec3 const& center_parameter, double radius_parameter);
	double area() const override;
	double volume() const override;
private:
	std::string name_;
	glm::vec3 color_;
	glm::vec3 center_;
	double radius_;
};

#endif