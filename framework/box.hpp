#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {
public:
	Box(std::string const& name_parameter, glm::vec3 const& color_parameter, glm::vec3 const& maximum_parameter, glm::vec3 const& minimum_parameter);
	double area() const override;
	double volume() const override;
private:
	std::string name_;
	glm::vec3 color_;
	glm::vec3 maximum_;
	glm::vec3 minimum_;
};

#endif