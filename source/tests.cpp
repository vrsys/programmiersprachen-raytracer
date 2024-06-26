#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include <glm/vec3.hpp>
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
