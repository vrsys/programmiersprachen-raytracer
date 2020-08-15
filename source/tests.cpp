#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp >

TEST_CASE("Sphere_Volume+Area", "[VolumeArea]")
{
    Sphere s1(glm::vec3(0, 0, 10), 5, "Sphere1", "Yellow");
    REQUIRE(s1.area() == Approx(314.16f));
    REQUIRE(s1.volume() == Approx(523.6f));
    Sphere s2(glm::vec3(0, 0, 0), 0, "Sphere2", "Yellow");
    REQUIRE(s2.area() == Approx(0.0f));
    REQUIRE(s2.area() == Approx(0.0f));
    Sphere s3(glm::vec3(9.2, -10, 10.121), 2, "Sphere3", "Yellow");
    REQUIRE(s3.area() == Approx(50.26548f));
    REQUIRE(s3.volume() == Approx(33.51f));
}

TEST_CASE("Box_Volume+Area", "[VolumeArea]")
{
    Box b1(glm::vec3(0, 0, 0), glm::vec3(2, 2, 2), "Box1", "Green");
    REQUIRE(b1.area() == Approx(24.0f));
    REQUIRE(b1.volume() == Approx(8.0f));
    Box b2(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), "Box2", "Green");
    REQUIRE(b2.area() == Approx(0.0f));
    REQUIRE(b2.area() == Approx(0.0f));
    Box b3(glm::vec3(-1, -1, -1), glm::vec3(-4, -4, -4), "Box3", "Green");
    REQUIRE(b3.area() == Approx(54.0f));
    REQUIRE(b3.volume() == Approx(27.0f));
}


TEST_CASE("intersect_ray_sphere", "[intersect]")
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
    
    Sphere s1(glm::vec3(0, 0, 10), 5, "Sphere1", "Yellow");
    Ray r1{ glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }};
    HitPoint h1 = s1.intersect(r1);
    REQUIRE(h1.distance == Approx(5.0f));
    REQUIRE(h1.color == "Yellow");
    REQUIRE(h1.name == "Sphere1");
    REQUIRE(h1.direction == r1.direction);
    REQUIRE(h1.intersection == glm::vec3(0,0,5));
    Sphere s2(glm::vec3(0, 10, 10), 5, "Sphere2", "Yellow");
    Ray r2{ glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, -1.0f, 2.0f } };
    HitPoint h2 = s2.intersect(r2);
    REQUIRE(h2.hashit == false);
    Sphere s3(glm::vec3(10, -10, 0), 8, "Sphere3", "Green");
    Ray r3{ glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 2.0f, -2.0f, 0.0f } };
    HitPoint h3 = s3.intersect(r3);
    REQUIRE(h3.hashit == true);
    REQUIRE(h3.distance == Approx(pow(200,0.5)-8));
    REQUIRE(h3.color == "Green");
    REQUIRE(h3.name == "Sphere3");
    REQUIRE(h3.direction == r3.direction);
}
TEST_CASE("dtor", "[destruction]") {
    glm::vec3 position{ 0.0f, 0.0f, 0.0f };
    Sphere* s1 = new Sphere{position ,1.2f, "Sphere0", "Red"};
    Shape* s2 = new Sphere{position ,1.2f, "Sphere", "Red"};
    s1->print(std::cout);
    std::cout << std::endl;
    s2->print(std::cout);
    std::cout << std::endl;
    delete s1;
    delete s2;
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
