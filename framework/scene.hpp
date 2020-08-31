#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>
#include <vector>
#include "camera.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "material.hpp"



struct Scene
{
	unsigned width, height;
	std::string filename;
	std::shared_ptr<Color> ambient{};
	std::vector<std::shared_ptr<Shape>> objects{};
	std::vector<std::shared_ptr<Light>> lights{};
	std::map<std::string, std::shared_ptr<Material>> materials{};
	std::shared_ptr<Camera> camera = nullptr;

};

#endif
