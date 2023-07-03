#include <glm/vec3.hpp>
#include "shape.hpp"
#include "Box.hpp"
#include "color.hpp"
#include "material.hpp"
#include <string>

#define OWN_PI 3.14159265359


Box::Box(glm::vec3 const& min, glm::vec3 const& max) : Shape{}, min_{ min }, max_{ max } {
};

Box::Box(std::string const& name, glm::vec3 const& min, glm::vec3 const& max, std::shared_ptr<Material> const& material) :
	Shape{ name, material},
	min_{ min },
	max_{ max } {
	if (max_.x < min_.x) {
		std::swap(max_.x, min_.x);
	}
	if (max_.y < min_.y) {
		std::swap(max_.y, min_.y);
	}
	if (max_.z < min_.z) {
		std::swap(max_.z, min_.z);
	}
}

float Box::area() const{
	glm::vec3 quad = max_ - min_;
	float area = 2 *(abs(quad.x * quad.y) + abs(quad.x * quad.z) + abs(quad.y * quad.z));
	return area;
}

float Box::volume() const{
	glm::vec3 quad = max_ - min_;
	return abs(quad.x * quad.y * quad.z);
}

std::ostream& Box::print(std::ostream& os)const {
	Shape::print(os);
	os << "Minimum: " << "{" << min_.r << "; " << min_.g << "; " << min_.b << "};" << "Maximum: " << "{" << max_.r << "; " << max_.g << "; " << max_.b << "};";
	return os;
}