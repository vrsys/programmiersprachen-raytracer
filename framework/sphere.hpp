#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include "color.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
	Sphere(std::string const& name_parameter, Color const& color_parameter, glm::vec3 const& center_parameter, double radius_parameter);
	double area() const override;
	double volume() const override;
	std::ostream& print(std::ostream& os) const override;
	HitPoint intersect(Ray & ray_, float intersection_distance_parameter) const;
private:
	glm::vec3 center_;
	double radius_;
};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif