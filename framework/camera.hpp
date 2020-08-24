#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <string>


struct Camera {


    Camera();
    Camera(std::string const& name ,glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& right, glm::vec3 const& down);


    std::string name_ = "Camera";
    glm::vec3 campos;
    glm::vec3 camdir;
    glm::vec3 camright;
    glm::vec3 camdown;
};

#endif