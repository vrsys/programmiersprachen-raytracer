//
// Created by Polina on 07.07.2024.
//

#include <string>
#include "shape.hpp"
#include "vector"
#include "map"

#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

struct Scene{
    int x_res_, y_res_;
    std::string file_name_;
    std::vector<Shape> shapes_;
    std::map<std::string ,std::shared_ptr<Material>> materials_;

};


#endif //RAYTRACER_SCENE_HPP
