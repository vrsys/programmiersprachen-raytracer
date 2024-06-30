#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include "color.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {
public:
	Box(std::string const& name_parameter, Color const& color_parameter, glm::vec3 const& maximum_parameter, glm::vec3 const& minimum_parameter);
	~Box();
	double area() const override;
	double volume() const override;
	std::ostream& print(std::ostream& os) const override;
private:
	glm::vec3 maximum_;
	glm::vec3 minimum_;
};

std::ostream& operator<<(std::ostream& os, Box const& b);

#endif