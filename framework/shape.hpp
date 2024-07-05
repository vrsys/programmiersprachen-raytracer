#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include "color.hpp"
#include "ray.hpp"
#include "hit_point.hpp"

class Shape {
public:
	Shape(std::string const& name, Color const& color);
	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;
	virtual ~Shape();
	virtual HitPoint intersect(Ray const& ray) const = 0;
protected:
	std::string name_;
	Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif