#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "camera.hpp"
#include "shape.hpp"
#include "light.hpp"



struct Scene
{
	unsigned width, height;
	std::string filename;
	std::shared_ptr<glm::vec3> ambient{};
	std::vector<std::shared_ptr<Shape>> objects{};
	std::vector<std::shared_ptr<Light>> lights{};

};

#endif
