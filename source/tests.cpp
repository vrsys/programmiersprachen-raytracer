#define CATCH_CONFIG_RUNNER
#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "hitpoint.hpp"
#include "color.hpp"
#include "material.hpp"
#include "sdf_reader.hpp"
#include "scene.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <catch.hpp>
#include <vector>

//Tests for the ex. 6.6:
bool operator<(std::shared_ptr<Material> const& lhs, std::shared_ptr<Material> const& rhs)
{
	return lhs->name < rhs->name;
};
std::shared_ptr<Material> vec_search(std::string name, std::vector<std::shared_ptr<Material>> vector_test )
{
	for (std::shared_ptr<Material> vec : vector_test) {
		if (vec->name == name) { return vec; }
	}
	return nullptr; 
};
std::shared_ptr<Material> set_search(std::string name, std::set<std::shared_ptr<Material>> set_test)
{
	std::shared_ptr<Material> mySharedPtr(new Material{ name, {0,0,0 },{1,0,0 },{1,0,0 },20 });
	auto it= set_test.find(mySharedPtr);
	if (it == set_test.end()) {
		return nullptr;
	}
	else { return *it; }
};
std::shared_ptr<Material> map_search(std::string name, std::map<std::string, std::shared_ptr<Material>> map_test)
{
	auto it = map_test.find(name);
	if (it == map_test.end()) {
		return nullptr;
	}
	else { return it->second; }

};
//----------------------------------

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}

TEST_CASE("Box and Sphere")
{
	Material material{ "placeholder", {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 };
	std::shared_ptr<Material> material_ = std::make_shared<Material>(material);
	Sphere sphere_0{ "name", material_, {0, 0, 0}, 0};
	Sphere sphere_1 { "name", material_, {5, 3, 2}, 2.5 };
	Box box_0{ "name", material_, {0, 0, 0}, {0, 0, 0 } };
	Box box_1 { "name", material_, {5, 3, 2}, {2, 1, 0} };
	Box box_2{ "name", material_, {1.5, 9.4, 7.2}, {-1.2, -4.1, -3.3} };

	std::cout << sphere_1;
	std::cout << box_2;

	CHECK(box_0.area() == 0);
	CHECK(box_0.volume() == 0);

	CHECK(box_1.area() == 32);
	CHECK(box_1.volume() == 12);

	CHECK(box_2.area() == Approx(413.1));
	CHECK(box_2.volume() == Approx(382.725));

	CHECK(sphere_0.area() == 0);
	CHECK(sphere_0.volume() == 0);

	CHECK(sphere_1.area() == Approx(78.54));
	CHECK(sphere_1.volume() == Approx(65.45));
}

TEST_CASE("intersect_ray_sphere", "[intersect]")
{
	// Ray
	glm::vec3 ray_origin{ 0.0f , 0.0f , 0.0f };
	// ray direction has to be normalized !
	// you can use :
	// v = glm :: normalize ( some_vector )
	glm::vec3 ray_direction{ 0.0f , 0.0f , 1.0f };
	// Sphere
	glm::vec3 sphere_center{ 0.0f ,0.0f , 5.0f };
	float sphere_radius{ 1.0f };
	float distance = 0.0f;
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction,
		sphere_center,
		sphere_radius * sphere_radius, // squared radius !!!
		distance);
	REQUIRE(distance == Approx(4.0f));

	Material material{ "placeholder", {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 };
	std::shared_ptr<Material> material_ = std::make_shared<Material>(material);

	Sphere sphere_0{ "sphere_0", material_, { -1, 0, 0 }, 1 };
	Sphere sphere_1{ "sphere_1", material_, { 0, 7.51, 0 }, 1 };
	Sphere sphere_2{ "sphere_2", material_, { -1.14, -2.68, 0 }, 3.0974 };

	Ray ray_0{ { 9.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
	Ray ray_1{ { 0.0f, 11.0f, 0.0f }, { 0.0f, -11.0f, 2.0f } };

	float intersection_distance_parameter = -1;

	HitPoint hitpoint_0 = sphere_0.intersect(ray_0); // yes
	HitPoint hitpoint_1 = sphere_1.intersect(ray_0); // no
	HitPoint hitpoint_2 = sphere_2.intersect(ray_0); // yes

	HitPoint hitpoint_3 = sphere_0.intersect(ray_1); // no
	HitPoint hitpoint_4 = sphere_1.intersect(ray_1); // yes
	HitPoint hitpoint_5 = sphere_2.intersect(ray_1); // yes

	CHECK(hitpoint_0.did_intersect_);
	CHECK(hitpoint_0.distance_ == 9);
	CHECK(hitpoint_0.object_name_ == "sphere_0");/*
	CHECK(hitpoint_0.object_color_.r == 0);
	CHECK(hitpoint_0.object_color_.g == 0.5);
	CHECK(hitpoint_0.object_color_.b == 0.7f);*/
	CHECK(hitpoint_0.position_ == glm::vec3{ 0, 0, 0 });
	CHECK(hitpoint_0.direction_ == ray_0.direction);

	CHECK(!hitpoint_1.did_intersect_);

	CHECK(hitpoint_2.did_intersect_);
	CHECK(hitpoint_2.distance_ == Approx(8.57).margin(0.02));
	CHECK(hitpoint_2.object_name_ == "sphere_2");/*
	CHECK(hitpoint_2.object_color_.r == 0);
	CHECK(hitpoint_2.object_color_.g == 0.5);
	CHECK(hitpoint_2.object_color_.b == 0.7f);*/
	CHECK(hitpoint_2.position_.x == Approx(0.43).margin(0.02));
	CHECK(hitpoint_2.position_.y == 0);
	CHECK(hitpoint_2.position_.z == 0);
	CHECK(hitpoint_2.direction_ == ray_0.direction);

	CHECK(!hitpoint_3.did_intersect_);

	CHECK(hitpoint_4.did_intersect_);
	CHECK(hitpoint_4.distance_ == Approx(2.47).margin(0.3));
	CHECK(hitpoint_4.object_name_ == "sphere_1");/*
	CHECK(hitpoint_4.object_color_.r == 0);
	CHECK(hitpoint_4.object_color_.g == 0.5);
	CHECK(hitpoint_4.object_color_.b == 0.7f);*/
	CHECK(hitpoint_4.position_.x == 0);
	CHECK(hitpoint_4.position_.y == Approx(8.57).margin(0.3));
	CHECK(hitpoint_4.position_.z == Approx(0.44).margin(0.3));
	CHECK(hitpoint_4.direction_ == ray_1.direction);

	CHECK(hitpoint_5.did_intersect_);
	CHECK(hitpoint_5.distance_ == Approx(11.93).margin(0.1));
	CHECK(hitpoint_5.object_name_ == "sphere_2");/*
	CHECK(hitpoint_5.object_color_.r == 0);
	CHECK(hitpoint_5.object_color_.g == 0.5);
	CHECK(hitpoint_5.object_color_.b == 0.7f);*/
	CHECK(hitpoint_5.position_.x == 0);
	CHECK(hitpoint_5.position_.y == Approx(-0.74).margin(0.1));
	CHECK(hitpoint_5.position_.z == Approx(2.13).margin(0.1));
	CHECK(hitpoint_5.direction_ == ray_1.direction);
}

TEST_CASE("box intersection")
{
	Material material{ "placeholder", {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 };
	std::shared_ptr<Material> material_ = std::make_shared<Material>(material);

	Box box_0{ "name", material_, { 0, 0, 0 }, { 0, 0, 0 } };
	Box box_1{ "name", material_, { 0, 5, 3 }, { -3, 2, 0 } };
	Box box_2{ "name", material_, { 3.67, -1.25, 4.92 }, { 1.75, -3.17, 3 } };
	Box box_3{ "name", material_, { -4.11, -4.27, -2.11 }, { -6, -6.16, -4 } };

	Ray ray_0{ { -3, 5, 0 }, { 6.67, -8.17, 4.92 } }; // starts in box_1, goes through box_1, intersects with box_2
	Ray ray_1{ { 9, 0, 0 }, { -15, -6.16, -4 } }; // intersects with box_3

	HitPoint hitpoint_0 = box_0.intersect(ray_0);
	HitPoint hitpoint_1 = box_1.intersect(ray_0);
	HitPoint hitpoint_2 = box_2.intersect(ray_0);
	HitPoint hitpoint_3 = box_3.intersect(ray_0);
	HitPoint hitpoint_4 = box_0.intersect(ray_1);
	HitPoint hitpoint_5 = box_1.intersect(ray_1);
	HitPoint hitpoint_6 = box_2.intersect(ray_1);
	HitPoint hitpoint_7 = box_3.intersect(ray_1);

	CHECK(hitpoint_0.did_intersect_ == false);

	CHECK(hitpoint_1.did_intersect_);
	CHECK(hitpoint_1.position_ == glm::vec3{ -3, 5, 0 });

	CHECK(hitpoint_2.did_intersect_);
	CHECK(hitpoint_2.position_.x == Approx(2.10251));
	CHECK(hitpoint_2.position_.y == -1.25);
	CHECK(hitpoint_2.position_.z == 3.76377f);

	CHECK(hitpoint_3.did_intersect_ == false);

	CHECK(hitpoint_4.did_intersect_ == false);
	CHECK(hitpoint_5.did_intersect_ == false);
	CHECK(hitpoint_6.did_intersect_ == false);

	CHECK(hitpoint_7.did_intersect_);
	CHECK(hitpoint_7.position_.x == Approx(- 4.11));
	CHECK(hitpoint_7.position_.y == Approx(- 5.38384));
	CHECK(hitpoint_7.position_.z == Approx(- 3.496));
}

TEST_CASE("static and dynamic type")
{
	Material material{ "placeholder", {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 };
	std::shared_ptr<Material> material_ = std::make_shared<Material>(material);

	Color red{ 255 , 0 , 0 };
	glm::vec3 position{ 0.0f , 0.0f , 0.0f };
	std::shared_ptr<Sphere> s1 =
		std::make_shared<Sphere>("sphere0", material_, position, 1.2f);
	std::shared_ptr<Shape> s2 =
		std::make_shared<Sphere>("sphere1", material_, position, 1.2f);
	s1->print(std::cout);
	s2->print(std::cout);
}


TEST_CASE("constructor, destructor order")
{
	Material material{ "placeholder", {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0 };
	std::shared_ptr<Material> material_ = std::make_shared<Material>(material);

	// if virtual: c Shape, c Sphere, c Shape, c Sphere | d Sphere, d Shape, d Sphere, d Shape
	// no virtual: c Shape, c Sphere, c Shape, c Sphere | d Sphere, d Shape, d Shape
	std::cout << "_______________________________________________________________________\n";
	Color red{ 255 , 0 , 0 };
	glm::vec3 position{ 0.0f , 0.0f , 0.0f };
	Sphere* s1 = new Sphere{ "sphere0", material_, position, 1.2f};
	Shape* s2 = new Sphere{ "sphere0", material_, position, 1.2f};
	s1->print(std::cout); // type Sphere: Sphere destructor called, Shape destructor called automatically
	s2->print(std::cout); // type Shape: only shape destructor called
	delete s1;
	delete s2;
}
//---------------------------------------
TEST_CASE("sdf file reader")
{
	// will obviously not work anywhere besides my laptop
	std::string const path = "C:\\Users\\User\\Dropbox\\Software Engineering I Programmiersprachen\\Uebungen\\programmiersprachen-raytracer\\example.sdf";
	// Anton: std::string const path = "C:\\university\\computer_science\\SoSe2024\\SE_I\\programmiersprachen-raytracer\\example.sdf";
	
	Scene incorrect_file_path{ read_sdf_file("nonsense") };

	Scene test_scene{ read_sdf_file(path) };
	for (std::shared_ptr<Material> material : test_scene.materials)
	{
		std::cout << *material << '\n';
	}

	//------------- Tests for ex. 6.6
	std::vector<std::shared_ptr<Material>> vector_test; 
	std::set<std::shared_ptr<Material>> set_test;
	std::map<std::string, std::shared_ptr<Material>> map_test;

	//Fill the containers
	for (std::shared_ptr<Material> material : test_scene.materials)
	{
		vector_test.push_back(material);
		set_test.insert(material);
		map_test.insert({ material->name, material });
	}
	//check of the working

	//Vector_test (Complexity N - linear):
	CHECK(vec_search("red", vector_test)->name =="red");
	CHECK(vec_search("yellow", vector_test) == nullptr);
	

	//Set_test (Complexity Logarithmic in size)
	CHECK(set_search("red", set_test)->name=="red");
	CHECK(set_search("yellow", set_test) == nullptr);


	//Map O(log(n))
	 std::string name6 = "red";
	 CHECK(map_search(name6, map_test)->name == "red");
	 CHECK(map_search("yellow", map_test) == nullptr);

}
