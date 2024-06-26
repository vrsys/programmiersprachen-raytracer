#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include "color.hpp"

class Shape {
public:
	Shape(std::string const& name, Color const& color);
	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;
	virtual ~Shape();
protected:
	std::string name_;
	Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif