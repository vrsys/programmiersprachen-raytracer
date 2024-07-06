#include "ray.hpp"
#include <cmath>
#include <iostream>

Ray norm(Ray const& ray) {
	float length = std::sqrt(ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y +
		ray.direction.z * ray.direction.z);
	Ray ret_ray{ ray.origin, {ray.direction.x / length, ray.direction.y / length, ray.direction.z / length} };
	return ret_ray;
}