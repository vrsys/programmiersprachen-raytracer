#ifndef BOX_HPP
#define BOX_HPP
#define GLM_SWIZZLE
#include <glm/vec3.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "shape.hpp"
#include <vector>

class Box : public Shape {
	glm::vec3 min_;
	glm::vec3 max_;
public:
	Box(glm::vec3& min, glm::vec3& max, std::string name, Material material);
	float area();
	float volume();
	std::ostream& print(std::ostream& os) const override;
	HitPoint intersect(Ray const& r) const;
	~Box();
	

};
#endif