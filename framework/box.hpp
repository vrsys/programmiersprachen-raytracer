#pragma once

#include <glm/vec3.hpp>
#include <string>
#include "shape.hpp"
#include "color.hpp"
#include "Ray.hpp"
#include "hitpoint.hpp"


class Box : public Shape {
public:
	Box()  = default;
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(std::string const& name, glm::vec3 const& min, glm::vec3 const& max, Color const& color);
	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const;
	HitPoint intersect(Ray const& r);
	~Box() {
		//std::cout << "\n" << "Box destroyed"; 
	};

private: 
	glm::vec3 min_ = { 0,0,0 };
	glm::vec3 max_ = { 0,0,0 };
};