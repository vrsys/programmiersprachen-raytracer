#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "shape.hpp"
#include ""

struct Scene {
	std::vector<Shape> shape_container;
	std::vector<Material> material_container;

};

Scene parse_sdf(std::string const& sdf_path);

#endif 