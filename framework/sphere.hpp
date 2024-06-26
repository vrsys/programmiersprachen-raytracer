#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "hit_point.hpp"
#include "ray.hpp"

class Sphere : public Shape {
public:
	Sphere(std::string const& name, Color const& color, glm::vec3 const& center, float radius);
	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const override;
	HitPoint intersect(Ray const& ray) const;
	~Sphere() override;
private:
	glm::vec3 center_;
	float radius_;
};

#endif