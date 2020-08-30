#include "glm/ext.hpp"
#include "box.hpp"
#include <catch-1.5\catch.hpp>

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

HitPoint Box::intersect(Ray const& ray) const
{
	std::vector<HitPoint> hits_vec{};
	HitPoint hit;

	// left surface
	// ray is not parallel to x plane
	if (ray.direction.x != Approx(0.0f)) {
	
		// intersection with plane
		float t = (min_.x - ray.origin.x) / ray.direction.x;
		float x = ray.origin.x + t * ray.direction.x;
		float y = ray.origin.y + t * ray.direction.y;
		float z = ray.origin.z + t * ray.direction.z;

		//intersection is on box
		if (t > 0 && y >= min_.y && y <= max_.y && z <= min_.z && z >= max_.z) {
			float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction };
			hits_vec.push_back(hit);
		}
	}

	//right surface
	//ray is not parallel to x plane
	if (ray.direction.x != Approx(0.0f)) {

		//intersection with plane
		float t = (max_.x - ray.origin.x) / ray.direction.x;
		float x = ray.origin.x + t * ray.direction.x;
		float y = ray.origin.y + t * ray.direction.y;
		float z = ray.origin.z + t * ray.direction.z;

		//intersection is on box
		if (t > 0 && y >= min_.y && y <= max_.y && z <= min_.z && z >= max_.z) {
			float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2)); // distance between starting point of ray and intersection point
			HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction };
			hits_vec.push_back(hit);
		}
	}

	// bottom surface 
	//ray is not parallel to y plane
	if (ray.direction.y != Approx(0.0f)) {

		//intersection with plane
		float t = (min_.y - ray.origin.y) / ray.direction.y;
		float x = ray.origin.x + t * ray.direction.x;
		float y = ray.origin.y + t * ray.direction.y;
		float z = ray.origin.z + t * ray.direction.z;

		//if intersection is on box
		if (t > 0 && x >= min_.x && x <= max_.x && z <= min_.z && z >= max_.z) {
			float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction };
			hits_vec.push_back(hit);
		}
	}


	// top surface
	//ray is not parallel to y plane
	if (ray.direction.y != Approx(0.0f)) {

		//intersection with plane
		float t = (max_.y - ray.origin.y) / ray.direction.y;
		float x = ray.origin.x + t * ray.direction.x;
		float y = ray.origin.y + t * ray.direction.y;
		float z = ray.origin.z + t * ray.direction.z;

		// if intersection is on box
		if (t > 0 && x >= min_.x && x <= max_.x && z <= min_.z && z >= max_.z) {
			float distance = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, distance, name_, material_, glm::vec3(x, y, z), ray.direction };
			hits_vec.push_back(hit);
		}
	}

	// front surface
	//ray is not parallel to z plane
	if (ray.direction.z != Approx(0.0f)) {

		//intersection with plane
		float t = (min_.z - ray.origin.z) / ray.direction.z;
		float x = ray.origin.x + t * ray.direction.x;
		float y = ray.origin.y + t * ray.direction.y;
		float z = ray.origin.z + t * ray.direction.z;

		//if intersection is on box
		if (t > 0 && y >= min_.y && y <= max_.y && x >= min_.x && x <= max_.x) {
			float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction };
			hits_vec.push_back(hit);
		}
	}


	// back surface
	//ray is not parallel to z plane
	if (ray.direction.z != Approx(0.0f)) {

		//intersection with plane
		float t = (max_.z - ray.origin.z) / ray.direction.z;
		float x = ray.origin.x + t * ray.direction.x;
		float y = ray.origin.y + t * ray.direction.y;
		float z = ray.origin.z + t * ray.direction.z;

		// check if intersection is on box
		if (y >= min_.y && y <= max_.y && x >= min_.x && x <= max_.x && t > 0) {
			float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction };
			hits_vec.push_back(hit);
		}
	}

	// if there was no hit
	if (hits_vec.empty()) {
		return HitPoint();
	}

	// find closest hit
	else {

		HitPoint closest_hit = hits_vec.at(0);

		for (auto it = 0; it < hits_vec.size(); ++it) {

			//glm::length returns the length of a vec
			double distance = glm::length(closest_hit.intersection - ray.origin);

			if (glm::length(hits_vec.at(it).intersection - ray.origin) < distance) {

				distance = glm::length(hits_vec.at(it).intersection - ray.origin);
				closest_hit = hits_vec.at(it);

			}
		}
		return closest_hit;
	}
}

Box::~Box()
{
	
	std::cout << "Box dtor:" << *this << std::endl;

}
