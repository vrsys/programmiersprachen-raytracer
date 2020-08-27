#include "glm/ext.hpp"
#include "box.hpp"

Box::Box(glm::vec3& min, glm::vec3& max, std::string name, Material material) : Shape(name, material)
{
	min_ = min;
	max_ = max;
}

float Box::area()
{
	return 2*abs(min_.x-max_.x)*abs(min_.y-max_.y)+ 2 * abs(min_.x - max_.x) * abs(min_.z - max_.z) + 2 * abs(min_.z - max_.z) * abs(min_.y - max_.y);
}

float Box::volume()
{
	return abs(min_.x - max_.x)*abs(min_.y - max_.y)*abs(min_.z - max_.z);
}

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	os << "Min:  " << glm::to_string(min_) << " Max: " << glm::to_string(max_);
	return os;
}

HitPoint Box::intersect(Ray const& r) const
{

	return HitPoint();
}

Box::~Box()
{
	
	std::cout << "Box dtor:" << *this << std::endl;

}
