//#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "shape.hpp"


struct Scene {

	std::vector<std::shared_ptr<Material>> material_container{};
	//std::vector<std::shared_ptr<Shape>> shape_container;
	//std::vector<std::shared_ptr<Camera>> camera_container;
	//std::vector<std::shared_ptr<Light>> light_container;

};

Scene parse_sdf(std::string const& sdf_path);

#endif 