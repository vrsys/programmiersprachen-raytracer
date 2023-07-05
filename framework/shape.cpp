#include "shape.hpp"
#include <string>

Shape::Shape(std::string const& name, std::shared_ptr<Material> const& material) : name_{ name }, material_{ material } {
};

std::ostream& Shape::print(std::ostream& os)const {
	os << "\n " << "Name: " << name_ <<  "Material: " << material_;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	s.print(os);
	return os;
}

std::pair<std::string, std::shared_ptr<Material>> Shape::get_n_c() {
	return std::pair<std::string, std::shared_ptr<Material>> {name_, material_};
}

std::string Shape::get_name() const {
	return name_;
}

std::shared_ptr<Material> Shape::get_material() const {
	return material_;
}
