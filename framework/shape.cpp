#include "shape.hpp"

Shape::Shape(std::string name, Color color) :
	name_{ name },
	color_{ color } {}

std::ostream& Shape::print(std::ostream& os) const {
	return os << "Name: " << name_ << "\n" <<
		"Color: " << color_;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return s.print(os);
}