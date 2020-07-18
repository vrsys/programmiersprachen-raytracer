#include <iostream>

class Shape {
	std::string name_;
	std::string color_;

public:
	Shape(std::string name, std::string color);
	virtual float area() = 0;
	virtual float volume() = 0;
};