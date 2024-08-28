#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include "sphere.hpp"

#include <string>
#include <map>
#include <vector>

struct Scene
{
	const std::map<std::string, std::shared_ptr<Material>> materials;
	const std::vector<std::shared_ptr<Shape>> shapes;

	//does this need a constructor definition here?
};

#endif