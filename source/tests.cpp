#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.hpp"
#include "shape.hpp"
#include "box.hpp"
#include <glm/vec3.hpp>

TEST_CASE(" sphere and box methods ", "[sphere_box_methods]") {
	Sphere s{ "sphere", {0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 12.34f };
	REQUIRE(1913.55123f == Approx(s.area()));
	REQUIRE(7871.074 == Approx(s.volume()));

	Box b{ "box", {0.0f, 0.0f, 0.0f}, glm::vec3{1.2f, 3.4f, 5.6f}, glm::vec3{7.8f, 9.0f, 10.2f} };
	REQUIRE(186.16f == Approx(b.area()));
	REQUIRE(170.016f == Approx(b.volume()));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
