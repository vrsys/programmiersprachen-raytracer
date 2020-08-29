
#include <fstream>  // open / read / write /close files
#include <sstream>  //stringstream -> easy parsing mechanics
#include <string>   // buffer lines read from file
#include <iostream> 
// #include <filesystem>
#include <direct.h>
#include <glm/vec3.hpp>
#include "renderer.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "box.hpp"


Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::render(Scene& scene)
{

    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            //for every pixel on our screen we need to find a ray going from origin to out 
            Ray ray = camera_ray(scene.camera, x, y);
            //trace the ray back into the scene
            Color pixel_color = trace(scene, ray);
            Pixel p{ (unsigned)x, (unsigned)y };
            p.color = pixel_color;
            write(p);
        }
    }
    ppm_.save(filename_);
}

Color Renderer::trace(Scene& scene, Ray& ray) {
    HitPoint min_dist_hitpoint;
    double min_dist = LONG_MAX;
    for (auto shape : scene.objects) {
        HitPoint hp = shape->intersect(ray);
        double dist = glm::distance(scene.camera->cam_pos, hp.intersection);
        if (dist > 0 && dist < min_dist) {
            min_dist = dist;
            min_dist_hitpoint = hp;
        }
    }
    if (min_dist == LONG_MAX) {
        //background color could be set in scenery 
        return (Color{ 0,0,0 });
    }
    else {
        /*
        * 
        * 
        */
        return (Color{ 1,1,1 });
    }

   
    return Color {0,0,0};
    }

Ray Renderer::camera_ray(std::shared_ptr<Camera> camera, int x, int y)
{
    /*
    * We currently have a window made of pixels, we want to convert this into rays to calculate intersections
    * this aims to turn a pixel value into a vector and then a ray which goes out from camera position to 
    * essentially map out our scene seen through our window
    */
    double normalized_x = (x + 0.5) / width_;
    double normalized_y = (y + 0.5) / height_;
    double window_space_x = (2 * normalized_x - 1) * ratio_;
    double window_space_y = (1 - 2 * normalized_x);
    //double scale =
    
    glm::vec3 dir{window_space_x, window_space_y, -1.0f};
    // std::shared_ptr<glm::vec3> ndir = std::make_shared<glm::vec3>(glm::normalize(dir));
    glm::vec3 ndir = glm::normalize(dir);
    //Does normalized do the right thing right now?
    return Ray{camera->cam_pos, ndir};
   
}


void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = width_ * p.y + p.x;
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

Scene Renderer::readScene(std::string const& filename) const {

    std::string line_buffer; //current line
    int32_t line_count = 0;
    std::string identifier;
    std::string class_name;
    std::string shape_name;
    Scene scene{};
    // open file in read-only && ASCII mode 
    std::ifstream in_file;
    in_file.exceptions(std::ifstream::badbit); 

    try {
        in_file.open(filename, std::ios::in);

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

                        Material material_sphere{};
                        auto sphere_material_pair = scene.materials.find(material_name_sphere);
                        material_sphere = *sphere_material_pair->second;

                        auto sphere = std::make_shared<Sphere>(glm::vec3(center.x, center.y, center.z), radius, sphere_name, material_sphere);
                                                    
                        scene.objects.push_back(sphere);

                    }
                    else if ("box" == shape_name) {
                        std::string box_name;
                        glm::vec3 min, max;
                        std::string material_name_box;
                        in_sstream >> box_name >> min.x >> min.y >> min.z >> max.x >> max.y >> max.z >> material_name_box;

                        Material material_box{};
                        auto box_material_pair = scene.materials.find(material_name_box);
                        material_box = *box_material_pair->second;
                        auto box = std::make_shared<Box>(glm::vec3(min.x, min.y, min.z), glm::vec3(max.x, max.y, max.z), box_name, material_box);
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
                    float fov;
                    float pos_x;
                    float pos_y;
                    float pos_z;
                    float dir_x;
                    float dir_y;
                    float dir_z;
                    float up_x;
                    float up_y;
                    float up_z;


                    in_sstream >> camera_name;
                    in_sstream >> fov;
                    in_sstream >> pos_x;
                    in_sstream >> pos_y;
                    in_sstream >> pos_z;
                    in_sstream >> dir_x;
                    in_sstream >> dir_y;
                    in_sstream >> dir_z;
                    in_sstream >> up_x;
                    in_sstream >> up_y;
                    in_sstream >> up_z;


                    std::shared_ptr<Camera> camera = std::make_shared<Camera>(camera_name, fov, glm::vec3(pos_x, pos_y, pos_z), glm::vec3(dir_x, dir_y, dir_z), glm::vec3(up_x, up_y, up_z));

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
                    std::cout << "Line was not valid: " << line_count << std::endl;
                }
            }

        }

        // close file
        in_file.close();
    }
    catch (std::ifstream::failure e) {
        // std::cerr << "Cannot open file " << filename << " in directory:" << std::filesystem::current_path() << "\n";
        char* cwd = _getcwd(NULL, 0);
        std::cerr << "Cannot open file " << filename << " in directory:" << cwd << "\n";
        free(cwd);
    }
    return scene;
}
