#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "hitpoint.hpp"
#include "color.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <catch.hpp>

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}

TEST_CASE("Box and Sphere")
{
	Sphere sphere_0{ "name", { 0, 0.5, 0.7 }, { 0, 0, 0 }, 0 };
	Sphere sphere_1 { "name", { 0, 0.5, 0.7 }, {5, 3, 2}, 2.5 };
	Box box_0{ "name", { 0, 0.5, 0.7 }, {0, 0, 0}, {0, 0, 0 } };
	Box box_1 { "name", { 0, 0.5, 0.7 }, {5, 3, 2}, {2, 1, 0} };
	Box box_2{ "name", { 0, 0.5, 0.7 }, {1.5, 9.4, 7.2}, {-1.2, -4.1, -3.3} };

	std::cout << sphere_1;
	std::cout << box_2;

	CHECK(box_0.area() == 0);
	CHECK(box_0.volume() == 0);

	CHECK(box_1.area() == 32);
	CHECK(box_1.volume() == 12);

	CHECK(box_2.area() == Approx(413.1));
	CHECK(box_2.volume() == Approx(382.725));

	CHECK(sphere_0.area() == 0);
	CHECK(sphere_0.volume() == 0);

	CHECK(sphere_1.area() == Approx(78.54));
	CHECK(sphere_1.volume() == Approx(65.45));
}

TEST_CASE("intersect_ray_sphere", "[intersect]")
{
	// Ray
	glm::vec3 ray_origin{ 0.0f , 0.0f , 0.0f };
	// ray direction has to be normalized !
	// you can use :
	// v = glm :: normalize ( some_vector )
	glm::vec3 ray_direction{ 0.0f , 0.0f , 1.0f };
	// Sphere
	glm::vec3 sphere_center{ 0.0f ,0.0f , 5.0f };
	float sphere_radius{ 1.0f };
	float distance = 0.0f;
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction,
		sphere_center,
		sphere_radius * sphere_radius, // squared radius !!!
		distance);
	REQUIRE(distance == Approx(4.0f));

	Sphere sphere_0{ "sphere_0", { 0.0f, 0.5f, 0.7f }, { -1, 0, 0 }, 1 };
	Sphere sphere_1{ "sphere_1", { 0.0f, 0.5f, 0.7f }, { 0, 7.51, 0 }, 1 };
	Sphere sphere_2{ "sphere_2", { 0.0f, 0.5f, 0.7f }, { -1.14, -2.68, 0 }, 3.0974 };

	Ray ray_0{ { 9.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
	Ray ray_1{ { 0.0f, 11.0f, 0.0f }, { 0.0f, -11.0f, 2.0f } };

	float intersection_distance_parameter = -1;

	HitPoint hitpoint_0 = sphere_0.intersect(ray_0); // yes
	HitPoint hitpoint_1 = sphere_1.intersect(ray_0); // no
	HitPoint hitpoint_2 = sphere_2.intersect(ray_0); // yes

	HitPoint hitpoint_3 = sphere_0.intersect(ray_1); // no
	HitPoint hitpoint_4 = sphere_1.intersect(ray_1); // yes
	HitPoint hitpoint_5 = sphere_2.intersect(ray_1); // yes

	CHECK(hitpoint_0.did_intersect_);
	CHECK(hitpoint_0.distance_ == 9);
	CHECK(hitpoint_0.object_name_ == "sphere_0");
	CHECK(hitpoint_0.object_color_.r == 0);
	CHECK(hitpoint_0.object_color_.g == 0.5);
	CHECK(hitpoint_0.object_color_.b == 0.7f);
	CHECK(hitpoint_0.position_ == glm::vec3{ 0, 0, 0 });
	CHECK(hitpoint_0.direction_ == ray_0.direction);

	CHECK(!hitpoint_1.did_intersect_);

	CHECK(hitpoint_2.did_intersect_);
	CHECK(hitpoint_2.distance_ == Approx(8.57).margin(0.02));
	CHECK(hitpoint_2.object_name_ == "sphere_2");
	CHECK(hitpoint_2.object_color_.r == 0);
	CHECK(hitpoint_2.object_color_.g == 0.5);
	CHECK(hitpoint_2.object_color_.b == 0.7f);
	CHECK(hitpoint_2.position_.x == Approx(0.43).margin(0.02));
	CHECK(hitpoint_2.position_.y == 0);
	CHECK(hitpoint_2.position_.z == 0);
	CHECK(hitpoint_2.direction_ == ray_0.direction);

	CHECK(!hitpoint_3.did_intersect_);

	CHECK(hitpoint_4.did_intersect_);
	CHECK(hitpoint_4.distance_ == Approx(2.47).margin(0.3));
	CHECK(hitpoint_4.object_name_ == "sphere_1");
	CHECK(hitpoint_4.object_color_.r == 0);
	CHECK(hitpoint_4.object_color_.g == 0.5);
	CHECK(hitpoint_4.object_color_.b == 0.7f);
	CHECK(hitpoint_4.position_.x == 0);
	CHECK(hitpoint_4.position_.y == Approx(8.57).margin(0.3));
	CHECK(hitpoint_4.position_.z == Approx(0.44).margin(0.3));
	CHECK(hitpoint_4.direction_ == ray_1.direction);

	CHECK(hitpoint_5.did_intersect_);
	CHECK(hitpoint_5.distance_ == Approx(11.93).margin(0.1));
	CHECK(hitpoint_5.object_name_ == "sphere_2");
	CHECK(hitpoint_5.object_color_.r == 0);
	CHECK(hitpoint_5.object_color_.g == 0.5);
	CHECK(hitpoint_5.object_color_.b == 0.7f);
	CHECK(hitpoint_5.position_.x == 0);
	CHECK(hitpoint_5.position_.y == Approx(-0.74).margin(0.1));
	CHECK(hitpoint_5.position_.z == Approx(2.13).margin(0.1));
	CHECK(hitpoint_5.direction_ == ray_1.direction);
}

TEST_CASE("static and dynamic type")
{
	Color red{ 255 , 0 , 0 };
	glm::vec3 position{ 0.0f , 0.0f , 0.0f };
	std::shared_ptr<Sphere> s1 =
		std::make_shared<Sphere>("sphere0", red, position, 1.2f);
	std::shared_ptr<Shape> s2 =
		std::make_shared<Sphere>("sphere1", red, position, 1.2f);
	s1->print(std::cout);
	s2->print(std::cout);
}


TEST_CASE("constructor, destructor order")
{
	// if virtual: c Shape, c Sphere, c Shape, c Sphere | d Sphere, d Shape, d Sphere, d Shape
	// no virtual: c Shape, c Sphere, c Shape, c Sphere | d Sphere, d Shape, d Shape
	std::cout << "_______________________________________________________________________\n";
	Color red{ 255 , 0 , 0 };
	glm::vec3 position{ 0.0f , 0.0f , 0.0f };
	Sphere* s1 = new Sphere{ "sphere0", red, position, 1.2f };
	Shape* s2 = new Sphere{ "sphere0", red, position, 1.2f };
	s1->print(std::cout); // type Sphere: Sphere destructor called, Shape destructor called automatically
	s2->print(std::cout); // type Shape: only shape destructor called
	delete s1;
	delete s2;
}