#include "box.hpp"

Box::Box(glm::vec3 min, glm::vec3 max)
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
