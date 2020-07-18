#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "box.hpp"
#include "sphere.hpp"


int main(int argc, char *argv[])
{
    Sphere s1(glm::vec3(0,0,0),5,"Sphere1","Yellow");
    std::cout << s1 << std::endl;
    return Catch::Session().run(argc, argv);
}
