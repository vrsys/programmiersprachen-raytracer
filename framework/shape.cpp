#include "shape.hpp"
#include <glm/gtx/transform.hpp>



Shape::Shape(std::string const& name, Material const& material) :
	name_{ name },
	material_{ material } {}


std::string Shape::name() const
{
	return name_;
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

Ray transformRay(Ray const& ray, glm::mat4 const& mat)
{    
	//homogenous coordinates
	glm::vec4 origin{ ray.origin , 1}; // 1 cause its a point
	glm::vec4 direction{ ray.direction , 0 }; // 0 cause its a vec

	origin = mat * origin;
	direction = mat * direction;

	return Ray{ {origin.x, origin.y, origin.z}, glm::normalize(glm::vec3(direction.x, direction.y, direction.z)) };

}

void Shape::translate(glm::vec3 const& axis)
{
	world_transformation_ = glm::translate(world_transformation_, axis);
	world_transformation_inv_ = glm::inverse(world_transformation_);
}


void Shape::scale(glm::vec3 const& axis)
{
	world_transformation_ = glm::scale(world_transformation_, axis);
	world_transformation_inv_ = glm::inverse(world_transformation_);
}


void Shape::rotate(float angle, glm::vec3 const& axis)
{

	world_transformation_ = glm::rotate(world_transformation_, angle, axis);
	world_transformation_inv_ = glm::inverse(world_transformation_);

}