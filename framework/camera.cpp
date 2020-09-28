#include "camera.hpp"

#define _USE_MATH_DEFINES
#include <math.h>



Camera::Camera():

	cam_pos{ glm::vec3{0.0f, 0.0f, 0.0f} },
	cam_dir{ glm::vec3{0.0f, 0.0f, -1.0f} },
	cam_up{ glm::vec3{0.0f, 1.0f, 0.0f} }{}





Camera::Camera(std::string const& name ,float fovx ,glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& up):
	name_{ name },
	fov_x{fovx},
	cam_pos{pos},
	cam_dir{dir},
	cam_up{up}{}

Ray Camera::camera_ray(int x, int y, unsigned width, unsigned height)
{    /*
    * We currently have a window made of pixels, we want to convert this into rays to calculate intersections
    * this aims to turn a pixel value into a vector and then a ray which goes out from camera position to
    * essentially map out our scene seen through our window
    */
    unsigned ratio_ = width / height;
    double normalized_x = (x + 0.5) / width;
    double normalized_y = (y + 0.5) / height;
    double window_space_x = (2 * normalized_x - 1) * ratio_;
    double window_space_y = (2 * normalized_y - 1);
    //scale fov
    double final_x = window_space_x * tan((fov_x * M_PI) / 180);
    double final_y = window_space_y * tan((fov_x * M_PI) / 180);

    glm::vec3 dir{ final_x, final_y, -1.0f };
    // std::shared_ptr<glm::vec3> ndir = std::make_shared<glm::vec3>(glm::normalize(dir));
    glm::vec3 ndir = glm::normalize(dir);
    Ray cam_norm_ray = { cam_pos , ndir };
    //if ((camera->cam_pos == glm::vec3{ 0, 0, 0 }) && (camera->cam_dir == glm::vec3{ 0, 0, -1 }) && (camera->cam_up == glm::vec3{ 0, 0, 0 })){
        //return cam_norm_ray;
    //}
    glm::mat4 transform_cam_matrix = transform_cam();
    //glm::vec4 origin_transformed_ray = glm::vec4 { camera->cam_pos, 1 } * transform_cam_matrix;
    //{origin_transformed_ray.x, origin_transformed_ray.y, origin_transformed_ray.z}
    glm::vec4 direction_transormed_ray = glm::vec4{ cam_norm_ray.direction, 0.0f } *transform_cam_matrix;
    Ray transformed_ray = { cam_pos,
       glm::normalize(glm::vec3 {direction_transormed_ray.x, direction_transormed_ray.y, direction_transormed_ray.z})
    };
    return transformed_ray;
	
}

glm::mat4 Camera::transform_cam()
{
    glm::vec3 n = cam_dir;
    if (n != glm::vec3{ 0, 0, 0 }) {
        n = glm::normalize(n);
    }
    glm::vec3 u = glm::cross(n, cam_up);
    if (u != glm::vec3{ 0, 0, 0 }) {
        u = glm::normalize(u);
    }
    glm::vec3 v = glm::cross(u, n);
    if (v != glm::vec3{ 0, 0, 0 }) {
        v = glm::normalize(v);
    }


    return glm::mat4
    { glm::vec4{u.x, u.y, u.z, 0 },
        glm::vec4{v.x, v.y, v.z, 0 },
        glm::vec4{-n.x, -n.y, -n.z, 0 },
        glm::vec4{cam_pos.x, cam_pos.y, cam_pos.z, 1}
    };
}



