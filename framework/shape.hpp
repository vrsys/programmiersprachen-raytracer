#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>

class Shape {
protected:

	std::string name_;
	std::string color_;

public:
	Shape(std::string name, std::string color);
	virtual float area() = 0;
	virtual float volume() = 0;
	virtual std::ostream& print(std::ostream& os) const;
	virtual ~Shape();

};
std::ostream& operator << (std::ostream& os, Shape const& s);
#endif