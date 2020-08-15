#include "shape.hpp"


Shape::Shape(std::string name, Color color)
{
	name_ = name;
	color_ = color;
}

std::ostream& Shape::print(std::ostream& os) const
{
	os << "Name: " << name_ << " Color: " << color_ << " ";
	return os;
}

Shape::~Shape()
{
	std::cout << "Shape dtor:" << *this << std::endl;
}

std::ostream& operator << (std::ostream& os, Shape const& s) {
	return s.print(os);
}
