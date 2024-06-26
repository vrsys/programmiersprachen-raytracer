#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <glm/vec3.hpp>

class Shape {
public:
	Shape(std::string const& name_parameter, glm::vec3 const& color_parameter);
	virtual double area() const = 0;
	virtual double volume() const = 0;
private:
	std::string name_;
	glm::vec3 color_;
};

#endif