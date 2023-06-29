#pragma once

#include <string>
#include "color.hpp"

class Shape {
public:
	
	Shape() = default;
	Shape(std::string const& name_, Color const& color);
	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;
	std::pair<std::string, Color> get_n_c();
	virtual ~Shape() {
		//std::cout << "\n" << "Shape destroyed" ;
	};

private:
	std::string name_ = "no_name";
	Color color_ = { 0,0,0 };
};

std::ostream& operator<<(std::ostream& os, Shape const& s);
