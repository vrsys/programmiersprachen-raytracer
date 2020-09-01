#include "shape.hpp"


Shape::Shape(std::string name, Material material)
{
	name_ = name;
	material_ = material;
}

std::ostream& Shape::print(std::ostream& os) const
{
	os << "Name: " << name_ << " ";
	return os;
}


Shape::~Shape()
{
	std::cout << "Shape dtor:" << *this << std::endl;
}


std::ostream& operator << (std::ostream& os, Shape const& s) {
	return s.print(os);
}

Ray Shape::transformRay(Ray const& ray, glm::mat4 const& mat)
{    
	//homogenous coordinates
	glm::vec4 origin{ ray.origin , 1}; // 1 cause its a point
	glm::vec4 direction{ ray.direction , 0 }; // 0 cause its a vec

	origin = mat * origin;
	direction = mat * direction;

	return Ray{ {origin.x, origin.y, origin.z}, glm::normalize(glm::vec3(direction.x, direction.y, direction.z)) };

}
