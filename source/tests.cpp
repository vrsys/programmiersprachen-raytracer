#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp >

TEST_CASE(" intersect_ray_sphere ", "[intersect]")
{
    // Ray
    glm::vec3 ray_origin{ 0.0f, 0.0f, 0.0f };
    // ray direction has to be normalized !
    // you can use :
    // v = glm :: normalize ( some_vector )
    glm::vec3 ray_direction{ 0.0f, 0.0f, 1.0f };
    // Sphere
    glm::vec3 sphere_center{ 0.0f ,0.0f, 5.0f };
    float sphere_radius{ 1.0f };
    float distance = 0.0f;
    auto result = glm::intersectRaySphere(
        ray_origin, ray_direction,
        sphere_center,
        sphere_radius * sphere_radius, // squared radius !!!
        distance);
    REQUIRE(distance == Approx(4.0f));
    std::cout << "Hello";
}


int main(int argc, char *argv[])
{
    Sphere s1(glm::vec3(0,0,0),5,"Sphere1","Yellow");
    std::cout << s1 << std::endl;
    Sphere s2(glm::vec3(5, -3, 0.1), 5, "Sphere2", "Cyan");
    std::cout << s2 << std::endl;
    Box b1(glm::vec3(0, 0, 0), glm::vec3(2, 2, 2), "Box1", "Green");
    std::cout << b1 << std::endl;
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;
    return Catch::Session().run(argc, argv);
}
