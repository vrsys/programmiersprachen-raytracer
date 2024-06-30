#include "shape.hpp"
#include "color.hpp"
#include <string>
#include <glm/vec3.hpp>

Shape::Shape(std::string const& name_parameter, Color const& color_parameter) : name_(name_parameter), color_(color_parameter) 
{
	std::cout << "Shape constructor called\n";
}

Shape::~Shape()
{
	std::cout << "Shape destructor called\n";
}

std::ostream& Shape::print(std::ostream& os) const
{
	return os << "name: " << name_ << " color: (" << color_.r << ", " << color_.g << ", " << color_.b << ')' << '\n';
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	return s.print(os);
}