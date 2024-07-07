#ifndef SDF_READER_HPP
#define SDF_READER_HPP

#include "material.hpp"
#include "scene.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

Scene read_sdf_file(std::string const& sdf_file_path)
{
	std::ifstream sdf_file(sdf_file_path); // an input stream that reads data from a file, ofstream would be used to create files

	if (!sdf_file.is_open())
	{
		std::cout << "Could not find or open: " << sdf_file_path << '\n';
		return Scene{}; // needs consideration
	}

	std::vector<std::shared_ptr<Material>> materials;

	std::string line_buffer; // individual lines are stored here


	while (std::getline(sdf_file, line_buffer)) // gets the next line from sdf_file and stores it in line_buffer
	{
		std::istringstream line_as_stream(line_buffer); // creates an input stream so that >> can be used to read from line_buffer

		std::string token; // a string to store words in (from whitespace to whitespace)

		line_as_stream >> token; // store the next word in token

		if (token == "define") // if it's define, we continue
		{
			line_as_stream >> token; // see what we're defining

			if (token == "material")
			{
				Material parsed_material; // create a material object

				// start filling the member variables
				line_as_stream >> parsed_material.name;

				// had to write operator[] for Color
				for (int ka_index = 0; ka_index < 3; ++ka_index)
				{
					line_as_stream >> parsed_material.ka[ka_index];
				}

				for (int kd_index = 0; kd_index < 3; ++kd_index)
				{
					line_as_stream >> parsed_material.kd[kd_index];
				}

				for (int ks_index = 0; ks_index < 3; ++ks_index)
				{
					line_as_stream >> parsed_material.ks[ks_index];
				}

				line_as_stream >> parsed_material.exponent;

				//std::cout << '\n' << parsed_material << '\n';

				materials.push_back(std::make_shared<Material>(parsed_material)); // the materials still exist after the function is done, because of the shared pointers
			}

			else
			{
				std::cout << "unexpected keyword: " << token << '\n';
			}
		}

		else
		{
			std::cout << "unexpected keyword: " << token << '\n';
		}
	}

	sdf_file.close();
	return Scene{ materials };
}

#endif