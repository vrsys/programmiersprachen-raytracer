#include "box.hpp"
#include "color.hpp"
#include "hitpoint.hpp"
#include <glm/vec3.hpp>
#include <limits>
#include <cmath>

Box::Box(std::string const& name_parameter, std::shared_ptr<Material> const& material_parameter, glm::vec3 const& maximum_parameter, glm::vec3 const& minimum_parameter) : Shape::Shape{ name_parameter, material_parameter }, maximum_(maximum_parameter), minimum_(minimum_parameter)
{
	std::cout << "Box constructor called\n";
}

Box::~Box()
{
	std::cout << "Box destructor called\n";
}

double Box::area() const {
	glm::vec3 diagonal_{ maximum_ - minimum_ };
	double a = std::abs(diagonal_.x);
	double b = std::abs(diagonal_.y);
	double c = std::abs(diagonal_.z);
	return 2 * (a * (b + c) + b * c);
}

double Box::volume() const {
	glm::vec3 diagonal_{ maximum_ - minimum_ };
	return std::abs(diagonal_.x * diagonal_.y * diagonal_.z);
}

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	return os << "maximum: (" << maximum_.x << ", " << maximum_.y << ", " << maximum_.z << ')' << " minimum: (" << minimum_.x << ", " << minimum_.y << ", " << minimum_.z << ')' << '\n';
}

std::ostream& operator<<(std::ostream& os, Box const& b)
{
	return b.print(os);
}

HitPoint Box::intersect(Ray const& ray_) const
{
	glm::vec3 ray_direction{ glm::normalize(ray_.direction) }; // normalize direction

	bool did_intersect = false;

	glm::vec3 intersection{};
	float t_parameter = std::numeric_limits<float>::max();

	float t = 0;

	auto better_t = [&t_parameter](float new_t) -> bool
		{
			return (new_t >= 0) && (new_t < t_parameter);
		};

	auto update_intersection = [&](glm::vec3 new_intersection, float new_t) -> void 
		{
			intersection = new_intersection;
			t_parameter = new_t;
			did_intersect = true;
		};

	if (ray_.direction.x != 0)
	{
		t = (minimum_.x - ray_.origin.x) / ray_direction.x;
		glm::vec3 intersection_x_min{ ray_.origin + t * ray_direction };
		if (better_t(t) && (minimum_.y <= intersection_x_min.y) && (intersection_x_min.y <= maximum_.y) && (minimum_.z <= intersection_x_min.z) && (intersection_x_min.z <= maximum_.z))
		{
			update_intersection(intersection_x_min, t);
		}
		// ...x_max plane
		t = (maximum_.x - ray_.origin.x) / ray_direction.x;
		glm::vec3 intersection_x_max{ ray_.origin + t * ray_direction };
		if (better_t(t) && (minimum_.y <= intersection_x_max.y) && (intersection_x_max.y <= maximum_.y) && (minimum_.z <= intersection_x_max.z) && (intersection_x_max.z <= maximum_.z))
		{
			update_intersection(intersection_x_max, t);
		}
	}
	// ...y_min plane
	if (ray_.direction.y != 0)
	{
		t = (minimum_.y - ray_.origin.y) / ray_direction.y;
		glm::vec3 intersection_y_min{ ray_.origin + t * ray_direction };
		if (better_t(t) && (minimum_.x <= intersection_y_min.x) && (intersection_y_min.x <= maximum_.x) && (minimum_.z <= intersection_y_min.z) && (intersection_y_min.z <= maximum_.z))
		{
			update_intersection(intersection_y_min, t);
		}
		// ...y_max plane
		t = (maximum_.y - ray_.origin.y) / ray_direction.y;
		glm::vec3 intersection_y_max{ ray_.origin + t * ray_direction };
		if (better_t(t) && (minimum_.x <= intersection_y_max.x) && (intersection_y_max.x <= maximum_.x) && (minimum_.z <= intersection_y_max.z) && (intersection_y_max.z <= maximum_.z))
		{
			update_intersection(intersection_y_max, t);
		}
	}
	// ...z_min plane
	if (ray_.direction.z != 0)
	{
		t = (minimum_.z - ray_.origin.z) / ray_direction.z;
		glm::vec3 intersection_z_min{ ray_.origin + t * ray_direction };
		if (better_t(t) && (minimum_.x <= intersection_z_min.x) && (intersection_z_min.x <= maximum_.x) && (minimum_.y <= intersection_z_min.y) && (intersection_z_min.y <= maximum_.y))
		{
			update_intersection(intersection_z_min, t);
		}
		// ...z_max plane
		t = (maximum_.z - ray_.origin.z) / ray_direction.z;
		glm::vec3 intersection_z_max{ ray_.origin + t * ray_direction };
		if (better_t(t) && (minimum_.x <= intersection_z_max.x) && (intersection_z_max.x <= maximum_.x) && (minimum_.y <= intersection_z_max.y) && (intersection_z_max.y <= maximum_.y))
		{
			update_intersection(intersection_z_max, t);
		}
	}
	return HitPoint{ did_intersect, t_parameter, Shape::name_, Shape::material_, intersection, ray_direction };
}