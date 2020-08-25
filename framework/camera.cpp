#include "camera.hpp"


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



