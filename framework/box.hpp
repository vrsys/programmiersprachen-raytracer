#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "material.hpp"

class Box : public Shape {
public:
	Box(std::string const& name, std::shared_ptr<Material> const& material, glm::vec3 const& min, glm::vec3 const& max);
	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const override;

private:
	glm::vec3 min_;
	glm::vec3 max_;
};

#endif