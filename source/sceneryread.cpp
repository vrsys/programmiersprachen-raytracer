#include <fstream>  // open / read / write /close files
#include <sstream>  //stringstream -> easy parsing mechanics
#include <string>   // buffer lines read from file
#include <iostream> 
#include <glm/vec3.hpp>
#include "scene.hpp"
#include "sphere.hpp"
#include "box.hpp"

int main(int argc, char** argv, Scene & scene) {

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <PATH_TO_SDF_FILE:string>" << std::endl;

        return -1;
    }

    std::string const in_file_path = argv[1];

    // open file in read-only && ASCII mode 
    std::ifstream in_file(in_file_path, std::ios::in);

    std::string line_buffer; //current line

    int32_t line_count = 0;


    std::string identifier;
    std::string class_name;
    std::string shape_name;

    while (std::getline(in_file, line_buffer)) {
        //std::cout << ++line_count << ": " << line_buffer << std::endl; 

        //construct stringstream using line_buffer string
        std::istringstream in_sstream(line_buffer);

        in_sstream >> identifier;

        //std::cout << "Identifier content: " << identifier << std::endl;

        // check for shapes / materials / lights
        if ("define" == identifier) {
            in_sstream >> class_name;

            // check for specific shape
            if ("shape" == class_name) {
                //check for shape type, then: parse attributes (including material lookup
                in_sstream >> shape_name;
                if ("sphere" == shape_name) {

                    std::string sphere_name;
                    glm::vec3 center;
                    float radius;
                    std::string material_name_sphere;
                    in_sstream >> sphere_name >> center.x >> center.y >> center.z >> radius >> material_name_sphere;

                    Material material_sphere {};
                    auto sphere_material_pair = scene.materials.find(material_name_sphere);
                    material_sphere = *sphere_material_pair->second;

                    auto sphere = std::make_shared<Sphere>( sphere_name , material_sphere , glm::vec3(center.x, center.y, center.z), radius);

                    scene.objects.push_back(sphere);

                }
                else if ("box" == shape_name) {
                    std::string box_name;
                    glm::vec3 min, max;
                    std::string material_name_box;
                    in_sstream >> box_name >> min.x >> min.y >> min.z >> max.x >> max.y >> max.z >> material_name_box;

                    Material material_box {};
                    auto box_material_pair = scene.materials.find(material_name_box);
                    material_box = *box_material_pair->second;
                    auto box = std::make_shared<Box>(box_name, material_box , glm::vec3(min.x, min.y, min.z), glm::vec3(max.x, max.y, max.z));
                    scene.objects.push_back(box);
                }
            }
            else if ("material" == class_name) {
                //parse material attributes
                std::string material_name;
                float ka_red, ka_green, ka_blue;
                float kd_red, kd_green, kd_blue;
                float ks_red, ks_green, ks_blue;
                float m;

                in_sstream >> material_name;
                in_sstream >> ka_red >> ka_green >> ka_blue; // 
                in_sstream >> kd_red >> kd_green >> kd_blue;
                in_sstream >> ks_red >> ks_green >> ks_blue;
                in_sstream >> m;

                Material added = { {ka_red, ka_green, ka_blue}, {kd_red, kd_green, kd_blue}, {ks_red, ks_green, ks_blue}, m };
                auto material = std::make_shared<Material>(added);
                scene.materials.insert(std::pair<std::string, std::shared_ptr<Material>>(material_name, material));
                std::cout << ka_red << " " << ka_green << " " << ka_blue << std::endl;

            }
            else if ("light" == class_name) {
                std::string light_name;
                float pos_x;
                float pos_y;
                float pos_z;
                float color_r;
                float color_g;
                float color_b;
                float brightness;

                in_sstream >> light_name;
                in_sstream >> pos_x;
                in_sstream >> pos_y;
                in_sstream >> pos_z;
                in_sstream >> color_r;
                in_sstream >> color_g;
                in_sstream >> color_b;
                in_sstream >> brightness;


                Color light_color{ color_r, color_g, color_b };

                std::shared_ptr<Light> light = std::make_shared<Light>(light_name, glm::vec3(pos_x, pos_y, pos_z), light_color, brightness);
                scene.lights.push_back(light);
            }
            else if (class_name == "camera") {
                //parse camera attribute
                std::string camera_name;
                float pos_x;
                float pos_y;
                float pos_z;
                float dir_x;
                float dir_y;
                float dir_z;
                float right_x;
                float right_y;
                float right_z;
                float down_x;
                float down_y;
                float down_z;

                in_sstream >> camera_name;
                in_sstream >> pos_x;
                in_sstream >> pos_y;
                in_sstream >> pos_z;
                in_sstream >> dir_x;
                in_sstream >> dir_y;
                in_sstream >> dir_z;
                in_sstream >> right_x;
                in_sstream >> right_y;
                in_sstream >> right_z;
                in_sstream >> down_x;
                in_sstream >> down_y;
                in_sstream >> down_z;

                std::shared_ptr<Camera> camera = std::make_shared<Camera>(camera_name,glm::vec3(pos_x,pos_y,pos_z), glm::vec3(dir_x, dir_y, dir_z), glm::vec3(right_x, right_y, right_z), glm::vec3(down_x, down_y, down_z));

                scene.camera = camera;
                  

            }
            else if (identifier == "ambient") {

            float ambient_r;
            float ambient_g;
            float ambient_b;

                in_sstream >> ambient_r >> ambient_g >> ambient_b;

                std::shared_ptr<glm::vec3> ambient = std::make_shared<glm::vec3>(ambient_r, ambient_g, ambient_b);
                scene.ambient = ambient;
            }
            else {
                std::cout << "Line was not valid!" << std::endl;
            }
        }

    }

    // close file
    in_file.close();
    return 0;
}
