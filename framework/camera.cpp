#include "camera.hpp"


Camera::Camera() :

	campos{ glm::vec3{0.0f, 0.0f, 0.0f} },
	camdir{ glm::vec3{0.0f, 0.0f, -1.0f} },
	camright{ glm::vec3{0.0f, 0.0f, 0.0f} },
	camdown{ glm::vec3{0.0f, 0.0f, 0.0f} }{}



Camera::Camera(glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& right, glm::vec3 const& down):
	campos{pos},
	camdir{dir},
	camright{right},
	camdown{down}{}



