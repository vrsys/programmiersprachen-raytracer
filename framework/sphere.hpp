#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "shape.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"
#include <color.hpp>

class Sphere : public Shape {
	glm::vec3 center_;
	float radius_;
public:

	Sphere(glm::vec3& center, float radius, std::string name, Color color);

	~Sphere();

	float area();
	float volume();
	std::ostream& print(std::ostream& os) const override;
	HitPoint intersect(Ray r);

};
#endif
