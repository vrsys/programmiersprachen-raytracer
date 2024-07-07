#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include <vector>

struct Scene
{
	const std::vector<std::shared_ptr<Material>> materials;
};

#endif