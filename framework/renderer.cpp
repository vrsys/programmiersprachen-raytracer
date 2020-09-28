
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
            Ray ray = scene.camera->camera_ray(x, y, width_, height_);
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
        return (Color{ 0.05,0.05,0.05 });
    }
    else {
        //shading to determin color 
        return (shading(scene, min_dist_hitpoint));
        //return (Color{ 1,1,1 });
    }

   

}

Color Renderer::shading(Scene& scene, HitPoint& hitpoint)
{
    //First we must look at what light hits our hitpoint
    std::vector<std::shared_ptr<Light>>lights{};
    if (hitpoint.intersection.x >= 0 && hitpoint.intersection.x <= 4 && hitpoint.intersection.y >= -100.2 && hitpoint.intersection.y <= -99.8 && hitpoint.intersection.z >= -300 && hitpoint.intersection.z <= -298) {
        std::cout << hitpoint.intersection.x << std::endl;
    }
    for (auto light : scene.lights) {

        glm::vec3 lightDir = hitpoint.intersection - light->pos_;
        glm::vec3 normLightDir = glm::normalize(lightDir);
        Ray lightRay{ light->pos_ , normLightDir };
        float dist = glm::distance(hitpoint.intersection, light->pos_);
        bool shadow = false;
       
        for (auto shape : scene.objects) {

            HitPoint hp = shape->intersect(lightRay);

            
            if (glm::distance(hp.intersection, light->pos_) < (dist - 0.2)) {
                shadow = true;
                break;
            }
            
        }
        if (shadow == false) {
            lights.push_back(light);
        }
        
    }
    
   

    float r_ambient = scene.ambient->r * hitpoint.material.ka_.r;
    float g_ambient = scene.ambient->g * hitpoint.material.ka_.g;
    float b_ambient = scene.ambient->b * hitpoint.material.ka_.b;
    float r_diffuse = 0;
    float g_diffuse = 0;
    float b_diffuse = 0;
    float r_specular = 0;
    float g_specular = 0;
    float b_specular = 0;


    if (lights.size() == 0) {
        if ((scene.ambient->r == 0) && (scene.ambient->g == 0) && (scene.ambient->b == 0)) {
            return Color{ 0,0,0 };
        }
        else {
            return Color{ scene.ambient->r * hitpoint.material.ka_.r, scene.ambient->g * hitpoint.material.ka_.g, scene.ambient->b * hitpoint.material.ka_.b };
        }
    }

    
    for (std::shared_ptr<Light> light : lights) {
        float cos0 = (glm::dot(glm::normalize(hitpoint.intersection - light->pos_), glm::normalize(hitpoint.normal)));
        float dif = (light->brightness_ * 0.01) * hitpoint.material.kd_.r * cos0 * light->color_.r;
        r_diffuse += (dif > 0) ? dif : 0;
        dif = (light->brightness_ * 0.01) * hitpoint.material.kd_.g * cos0 * light->color_.g;
        g_diffuse += (dif > 0) ? dif : 0; 
        dif = (light->brightness_ * 0.01) * hitpoint.material.kd_.b * cos0 * light->color_.b;
        b_diffuse += (dif > 0) ? dif : 0; 
        glm::vec3 normLight = glm::normalize(hitpoint.intersection - light->pos_);
        glm::vec3 r = (2 * glm::dot(normLight, glm::normalize(hitpoint.normal)) * glm::normalize(hitpoint.normal) - normLight);
        float cosb = pow(glm::dot(glm::normalize(hitpoint.intersection - scene.camera->cam_pos), r),hitpoint.material.m_);
        float spec = (light->brightness_ * 0.01) * hitpoint.material.ks_.r * cosb * light->color_.r;
        r_specular += (spec > 0) ? spec : 0;
        spec = (light->brightness_ * 0.01) * hitpoint.material.ks_.g * cosb * light->color_.g;
        g_specular += (spec > 0) ? spec : 0;
        spec = (light->brightness_ * 0.01) * hitpoint.material.ks_.b * cosb * light->color_.b;
        b_specular += (spec > 0) ? spec : 0; 
    }
   
    return Color{ r_ambient + r_diffuse + r_specular, g_ambient + g_diffuse + g_specular, b_ambient + b_diffuse + b_specular };
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
            if (identifier == "ambient") {

                float ambient_r = 0;
                float ambient_g = 0;
                float ambient_b = 0;

                in_sstream >> ambient_r >> ambient_g >> ambient_b;

                std::shared_ptr<Color> ambient = std::make_shared<Color>(ambient_r, ambient_g, ambient_b);
                scene.ambient = ambient;
            }

            else if ("define" == identifier) {
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
                    in_sstream >> ka_red >> ka_green >> ka_blue; 
                    in_sstream >> kd_red >> kd_green >> kd_blue;
                    in_sstream >> ks_red >> ks_green >> ks_blue;
                    in_sstream >> m;

                    Material added = { {ka_red, ka_green, ka_blue}, {kd_red, kd_green, kd_blue}, {ks_red, ks_green, ks_blue}, m };
                    auto material = std::make_shared<Material>(added);
                    scene.materials.insert(std::pair<std::string, std::shared_ptr<Material>>(material_name, material));
                    std::cout << ka_red << " " << ka_green << " " << ka_blue << std::endl;

                }
                else if ("light" == class_name) {
                    
                    Light light;
                    in_sstream >> light.name_ >> light.pos_.x >> light.pos_.y >> light.pos_.z >> light.color_.r >> light.color_.g >> light.color_.b >> light.brightness_;
                    light = light;
                    scene.lights.push_back(std::make_shared<Light>(light));
                    
                }
                else if (class_name == "camera") {
                    //parse camera attribute
                    Camera camera;
                    
                    in_sstream >> camera.name_;

                    in_sstream >> camera.fov_x;

                    in_sstream >> camera.cam_pos.x >> camera.cam_pos.y >> camera.cam_pos.z;
                    
                    in_sstream >> camera.cam_dir.x >> camera.cam_dir.y >> camera.cam_dir.z;

                    in_sstream >> camera.cam_up.x >> camera.cam_up.y >> camera.cam_up.z;
      
                    scene.camera = std::make_shared<Camera>(camera);
                }
                
                else {
                    std::cout << "Line was not valid: " << line_count << std::endl;
                }
            }

            else if (identifier == "transform") {
                std::string object_name, transformation_type;
                in_sstream >> object_name >> transformation_type;
                if (object_name == scene.camera->name_) {
                    if (transformation_type == "translate") {
                        float xt, yt, zt;
                        in_sstream >> xt >> yt >> zt;
                        scene.camera->cam_pos.x += xt;
                        scene.camera->cam_pos.y += yt;
                        scene.camera->cam_pos.z += zt;
                    }
                    else if (transformation_type == "rotate") {
                        float angle_degres, xr, yr, zr;
                        in_sstream >> angle_degres >> xr >> yr >> zr;
                        float angle = angle_degres / 180 * M_PI;
                        float x = scene.camera->cam_dir.x;
                        float y = scene.camera->cam_dir.y;
                        float z = scene.camera->cam_dir.z;
                        if (xr == 1) {
                            scene.camera->cam_dir.y = y * cos(angle) - z * sin(angle);
                            scene.camera->cam_dir.z = z * sin(angle) + y * cos(angle);
                        }
                        else if (xr == 0 && yr == 1) {
                            scene.camera->cam_dir.x = x * cos(angle) + z * sin(angle);
                            scene.camera->cam_dir.z = -x * sin(angle) + z * cos(angle);
                        }
                        else if (xr == 0 && yr == 0 && zr == 1) {
                            scene.camera->cam_dir.x = x * cos(angle) - y * sin(angle);
                            scene.camera->cam_dir.y = x * sin(angle) + y * cos(angle);
                        }

                    }
                    else {
                        std::cout << transformation_type << " is not viable for Camera" << std::endl;
                    }
                }
                else {
                    for (auto it : scene.objects) {
                        if ( it->name_ == object_name){
                            if (transformation_type == "translate") {
                                float x, y, z;
                                in_sstream >> x >> y >> z;
                                it->translate({ x,y,z });

                            }
                            else if (transformation_type == "rotate") {
                                float angle_degres, xr, yr, zr;
                                in_sstream >> angle_degres >> xr >> yr >> zr;
                                float angle = angle_degres / 180 * M_PI;
                                it->rotate(angle, { xr,yr,zr });
                            }
                            else if (transformation_type == "scale") {
                                float x, y, z;
                                in_sstream >> x >> y >> z;
                                it->scale({ x,y,z });
                            }
                        }
                    }
                   

                }
            }
            else if (identifier == "render") {
            unsigned height, width;
            std::string filename;
            std::string camera_name;

            in_sstream >> camera_name >> filename >> width >> height;

            scene.width = width;
            scene.height = height;
            scene.filename = filename;
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
