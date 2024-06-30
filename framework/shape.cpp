#include "shape.hpp"
#include <string>
#include <glm/vec3.hpp>

Shape::Shape(std::string const& name_parameter, glm::vec3 const& color_parameter) : name_(name_parameter), color_(color_parameter) 
{}

std::ostream& Shape::print(std::ostream& os) const
{
	return os << "name: " << name_ << " color: (" << color_.x << ", " << color_.y << ", " << color_.z << ')' << '\n';
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	return s.print(os);
}