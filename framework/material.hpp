#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP
#include <string>
#include "color.hpp"


struct Material{
    std::string name_;
    Color ka_,kd_,ks_;
    float m_;

    Material(const std::string& name, Color const& ka, Color const& kd, Color const& ks, float m);
    std::ostream& print(std::ostream& os) const;
};
std::ostream& operator<<(std::ostream& os,Material const& material);


#endif //RAYTRACER_MATERIAL_HPP
