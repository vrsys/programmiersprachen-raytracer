#include "shape.hpp"
#include <string>

Shape::Shape(std::string const& name, Color const& color) : name_{ name }, color_{ color } {};

std::ostream& Shape::print(std::ostream& os)const {
	os << "\n " << "Name: " << name_ << "; Color: {" << color_.r << "; " << color_.g << "; " << color_.b << "}; ";
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	s.print(os);
	return os;
}

std::pair<std::string, Color> Shape::get_n_c() {
	return std::pair<std::string, Color> {name_, color_};
}
