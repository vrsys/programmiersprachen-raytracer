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

HitPoint Box::intersect(Ray const& r) const
{
	Ray ray = transformRay(r, world_transformation_inv_);
	std::vector<HitPoint> hits_vec{}; //vector to store hitpoints
	HitPoint hit;


	// left surface
	if (ray.direction.x != Approx(0.0f)) {// if ray is not parallel to x plane
	
		// intersection with plane
		float t = (min_.x - ray.origin.x) / ray.direction.x; // according to slides  xmin = p0x + t.dx
		float x = ray.origin.x + t * ray.direction.x;
		float y = ray.origin.y + t * ray.direction.y;
		float z = ray.origin.z + t * ray.direction.z;

		//if intersection is on left surface
		if (t > 0 && y >= min_.y && y <= max_.y && z <= min_.z && z >= max_.z) { // Check if the y and z coordinates of  the intersection between ymin and ymax and zmin and zmax, z is different because of the defaut value of it
			float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));// distance between starting point of ray and intersection point
			HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction, glm::vec3 {-1,0,0} };// initialize our hit
			hits_vec.push_back(hit);
		}
	}

	    //right surface
	if (ray.direction.x != Approx(0.0f)) { // if ray is not parallel to x plane

		//intersection with plane
		float t = (max_.x - ray.origin.x) / ray.direction.x;
		float x = ray.origin.x + t * ray.direction.x;
		float y = ray.origin.y + t * ray.direction.y;
		float z = ray.origin.z + t * ray.direction.z;


		if (t > 0 && y >= min_.y && y <= max_.y && z <= min_.z && z >= max_.z) { //if the intersection is on right surface
				float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2)); // distance between starting point of ray and intersection point
				HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction, glm::vec3 {1,0,0} }; // initialize our hit 
				hits_vec.push_back(hit);
			}
		}
	

			// bottom surface 
			if (ray.direction.y != Approx(0.0f)) { // if ray is not parallel to y plane

				//intersection with plane
				float t = (min_.y - ray.origin.y) / ray.direction.y;
				float x = ray.origin.x + t * ray.direction.x;
				float y = ray.origin.y + t * ray.direction.y;
				float z = ray.origin.z + t * ray.direction.z;


				if (t > 0 && x >= min_.x && x <= max_.x && z <= min_.z && z >= max_.z) { // if intersection is on bottom surface
					float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));// distance between starting point of ray and intersection point
					HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction, glm::vec3 {0,-1,0} };
					hits_vec.push_back(hit);
					}
				}


				// top surface
				if (ray.direction.y != Approx(0.0f)) {  // if ray is not parallel to y plane

					//intersection with plane
					float t = (max_.y - ray.origin.y) / ray.direction.y;
					float x = ray.origin.x + t * ray.direction.x;
					float y = ray.origin.y + t * ray.direction.y;
					float z = ray.origin.z + t * ray.direction.z;


					// if intersection is on top surface
					if (t > 0 && x >= min_.x && x <= max_.x && z <= min_.z && z >= max_.z) {
						float distance = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2)); // distance between starting point of ray and intersection point
						HitPoint hit{ true, distance, name_, material_, glm::vec3(x, y, z), ray.direction, glm::vec3 {0,1,0} };
						if (hit.intersection.x >= 101 && hit.intersection.x <= 104 && hit.intersection.y >= -100.2 && hit.intersection.y <= -99.8 && hit.intersection.z >= -400 && hit.intersection.z <= -398) {
							hit.intersection;
						}

						hits_vec.push_back(hit);
					}
				}

				// front surface
				if (ray.direction.z != Approx(0.0f)) {  // if ray is not parallel to z plane

					// intersection with plane
					float t = (min_.z - ray.origin.z) / ray.direction.z;
					float x = ray.origin.x + t * ray.direction.x;
					float y = ray.origin.y + t * ray.direction.y;
					float z = ray.origin.z + t * ray.direction.z;


					if (t > 0 && y >= min_.y && y <= max_.y && x >= min_.x && x <= max_.x) { // if intersection is on surface
						float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2)); // distance between starting point of ray and intersection point
						HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction, glm::vec3 {0,0,1} };
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

					if (y >= min_.y && y <= max_.y && x >= min_.x && x <= max_.x && t > 0) { // check if intersection is on surface
						float d = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2)); // distance between starting point of ray and intersection point 
						HitPoint hit{ true, d, name_, material_, glm::vec3(x, y, z), ray.direction, glm::vec3 {0,0,-1} };
						hits_vec.push_back(hit);
					}
				}

				if (hits_vec.empty()) {
					return HitPoint();
				}

				// find closest hit
				else {

					HitPoint closest_hit = hits_vec.at(0);

					//glm::length returns the length of a vec
					//double distance = glm::length(closest_hit.intersection - ray.origin);

					for (auto it = 0; it < hits_vec.size(); ++it) {

						//glm::length returns the length of a vec
						double distance = glm::length(closest_hit.intersection - ray.origin);

						if (glm::length(hits_vec.at(it).intersection - ray.origin) < distance) { //if we can find a smaller distance than that is the closest hit

							distance = glm::length(hits_vec.at(it).intersection - ray.origin);

							glm::vec4 transformed_hitpoint = world_transformation_ * glm::vec4{ hits_vec.at(it).intersection, 1.0f };
							glm::vec4 transformed_normal = glm::transpose(world_transformation_inv_) * glm::vec4{ hits_vec.at(it).normal, 0.0f };
							hits_vec.at(it).intersection = { transformed_hitpoint.x, transformed_hitpoint.y, transformed_hitpoint.z };
							hits_vec.at(it).normal = glm::normalize(glm::vec3(transformed_normal.x, transformed_normal.y, transformed_normal.z));

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
		