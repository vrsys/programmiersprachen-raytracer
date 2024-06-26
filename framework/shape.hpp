#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <glm/vec3.hpp>
#include <iostream>

class Shape {
public:
	Shape(std::string const& name_parameter, glm::vec3 const& color_parameter);
	virtual double area() const = 0;
	virtual double volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;
private:
	std::string name_;
	glm::vec3 color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif