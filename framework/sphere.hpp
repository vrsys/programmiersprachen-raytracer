#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "hit_point.hpp"
#include "ray.hpp"

class Sphere : public Shape {
public:
	Sphere(std::string name, Color color, glm::vec3 const& center, float radius);
	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const override;
	HitPoint const& intersect(Ray const& ray) const;
private:
	std::string name_;
	Color color_;
	glm::vec3 center_;
	float radius_;
};

#endif