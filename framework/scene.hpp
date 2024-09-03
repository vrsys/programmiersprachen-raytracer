#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "camera.hpp"

#include <string>
#include <map>
#include <vector>

struct Scene
{
	const std::map<std::string, std::shared_ptr<Material>> materials;
	const std::map<std::string, std::shared_ptr<Shape>> shapes; //why exactly is this a map of shared pointers instead of just shapes?
	const std::vector<Light> lights;
	Camera camera;

	//does this need a constructor definition here?
};

#endif