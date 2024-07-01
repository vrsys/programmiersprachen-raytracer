#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include <string>
#include <glm/vec3.hpp>
#include <iostream>

class Shape {
public:
	Shape(std::string const& name_parameter, Color const& color_parameter);
	virtual ~Shape();
	virtual double area() const = 0;
	virtual double volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;
protected:
	std::string name_;
	Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif