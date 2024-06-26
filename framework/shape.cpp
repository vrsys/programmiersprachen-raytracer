#include "shape.hpp"
#include <string>
#include <glm/vec3.hpp>

Shape::Shape(std::string const& name_parameter, glm::vec3 const& color_parameter) : name_(name_parameter), color_(color_parameter) 
{}
