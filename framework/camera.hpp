#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <iostream> 
#include "ray.hpp"


struct Camera {


    Camera();
    Camera(std::string const& name ,float fovx ,glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& up);
    Ray camera_ray(int x, int y, unsigned width, unsigned height);
    glm::mat4 transform_cam();


    std::string name_ = "Camera";
    float fov_x = 45.0f;
    glm::vec3 cam_pos;
    glm::vec3 cam_dir;
    glm::vec3 cam_up;
};

#endif