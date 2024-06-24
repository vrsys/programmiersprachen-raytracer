#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
	Sphere();
	float area() const override;
	float volume() const override;
private:
	glm::vec3 center_;
	float radius_;
};

#endif