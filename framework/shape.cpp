#include "shape.hpp"


Shape::Shape(std::string name, std::string color)
{
	name_ = name;
	color_ = color;
}

std::ostream& operator << (std::ostream& os, Shape const& s) {
	return s.print(os);
}
