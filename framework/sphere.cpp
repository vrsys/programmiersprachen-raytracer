#include <glm/gtx/intersect.hpp>
#include "glm/ext.hpp"
#include "sphere.hpp"

Sphere::Sphere(glm::vec3& center, float radius, std::string name, Material material) : Shape(name, material)
{
	center_ = center;
	radius_ = radius;
}

float Sphere::area()
{
	return 4* M_PI* radius_* radius_;
}

float Sphere::volume()
{
	return (M_PI*pow(radius_,3)*(4.0f/3.0f));
}

std::ostream& Sphere::print(std::ostream& os) const
{
	Shape::print(os);
	os << "Center: " << glm::to_string(center_) << " Radius: " << radius_;
	return os;
}

HitPoint Sphere::intersect(Ray const& r) const
{
	/*HitPoint h;
	h.hashit = glm::intersectRaySphere(r.origin, glm::normalize(r.direction), center_,pow(radius_,2),h.distance);
	if (h.hashit == true) {
		h.material = material_;
		h.name = name_;
		h.direction = r.direction;
		h.intersection = r.origin + (glm::normalize(r.direction) * h.distance);
		h.normal = glm::normalize(h.intersection - center_);

	}
	return h;*/

	float distance = 0; //intersection distance
	Ray ray = transformRay(r, world_transformation_inv_);

	bool hit = glm::intersectRaySphere(ray.origin, ray.direction, center_, pow(radius_, 2), distance);

	glm::vec3 hitpoint = ray.origin + distance * ray.direction;
	glm::vec3 normal = hitpoint - center_;
	normal = glm::normalize(normal);

	glm::vec4 hitpoint_transformed = world_transformation_ * glm::vec4{ hitpoint, 1.0f }; // additional 1.0f for multiplying (homogenous coordinates)
	glm::vec4 transform_normal = glm::transpose(world_transformation_inv_) * glm::vec4{ normal, 0.0f };

	hitpoint = { hitpoint_transformed.x, hitpoint_transformed.y, hitpoint_transformed.z };
	normal = { transform_normal.x, transform_normal.y, transform_normal.z }; // das neue normal xd

	return HitPoint{ hit , distance , name_ ,material_ , hitpoint , ray.direction , normal };
}

Sphere::~Sphere()
{
	std::cout << "Sphere dtor:" << *this << std::endl;
}
