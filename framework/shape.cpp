#include "shape.hpp"


Shape::Shape(std::string name, Material material)
{
	name_ = name;
	material_ = material;
}

std::ostream& Shape::print(std::ostream& os) const
{
	os << "Name: " << name_ << " ";
	return os;
}

Shape::~Shape()
{
	std::cout << "Shape dtor:" << *this << std::endl;
}

std::ostream& operator << (std::ostream& os, Shape const& s) {
	return s.print(os);
}
