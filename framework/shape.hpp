#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>
#include <color.hpp>
#include "hitpoint.hpp"
#include "ray.hpp"
#include "material.hpp"
#include <glm/glm.hpp>

class Shape {
protected:

	std::string name_;
	Material material_;
	glm::mat4 world_transformation_{};
	glm::mat4 world_transformation_inv_{};

public:
	Shape(std::string name, Material material);
	virtual float area() = 0;
	virtual float volume() = 0;
	virtual std::ostream& print(std::ostream& os) const;
	virtual HitPoint intersect(Ray const& r)const = 0;
	virtual ~Shape();
	void translate(glm::vec3 const& axis);
	void scale(glm::vec3 const& axis);
	void rotate(float angle, glm::vec3 const& axis);

};

Ray transformRay(Ray const& ray, glm::mat4 const& mat);
std::ostream& operator << (std::ostream& os, Shape const& s);


#endif