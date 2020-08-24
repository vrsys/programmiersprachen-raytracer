#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"


class Material
{
public:
	Material();
	Material(Color ka, Color kd, Color ks, float m);

public:
	
	Color ka_;
	Color kd_;
	Color ks_;
	float m_;

};

#endif

