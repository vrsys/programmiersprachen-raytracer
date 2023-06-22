#pragma once

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"

class Sphere : public Shape {
public:
	Sphere()= default;
	Sphere(glm::vec3 const& mid_point, float radius);
	Sphere(std::string const& name, glm::vec3 const& mid_point, float radius, Color const& color);
	virtual float area() const;
	virtual float volume() const;
	HitPoint intersect(Ray const& ray, float & distance);
	virtual std::ostream& print(std::ostream& os) const;
	~Sphere() {};

private:
	glm::vec3 center_ = { 0,0,0 };
	float radius_ = 0;
};

