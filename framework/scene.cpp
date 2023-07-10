
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#include "scene.hpp"


Scene parse_sdf(std::string const& sdf_path) {
	

	Scene scene{};

	std::ifstream f_stream{sdf_path};

	if (!f_stream.is_open()) {
		std::cout << "Cannot open file\n";
		return scene;
	}
	
	std::string line_buffer;
	while (std::getline(f_stream, line_buffer)) {
		std::istringstream string_stream{ line_buffer };

		std::string token;

		string_stream >> token;

		if (token == "define") {
			string_stream >> token;
			if (token == "material") {
				std::string name;
				string_stream >> name;
				//std::cout << name;

				float value = 0.0f;

				std::array<float, 3> ka{};
				for (int i = 0; i < ka.size(); ++i) {
					string_stream >> value;
					ka[i] = value;
					//std::cout << ka[i];
				}

				std::array<float, 3> kd{};
				for (int i = 0; i < ka.size(); ++i) {
					string_stream >> value;
					kd[i] = value;
				}

				std::array<float, 3> ks{};
				for (int i = 0; i < ka.size(); ++i) {
					string_stream >> value;
					ks[i] = value;
				}

				float m = 0.0f;
				string_stream >> m;

				Material mat{ name, Color{ka[0], ka[1], ka[2]}, Color{kd[0], kd[1], kd[2]}, Color{ks[0], ks[1], ks[2]}, m };

				scene.material_container.push_back(std::make_shared<Material>(mat));

			}

		}

	}
	return scene;
}

