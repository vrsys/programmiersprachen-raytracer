#include "color.hpp"


class Material
{
public:
	Material(std::string name, Color ka, Color kd, Color ks, float m);

public:
	std::string name_;
	Color ka_;
	Color kd_;
	Color ks_;
	float m_;

};

