#include <renderer.hpp>
#include <window.hpp>
#include "material.hpp"
#include "scene.hpp"
#include "sdf_reader.hpp"
#include "ray.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

#include <glm/vec3.hpp>
#include <vector>
#include <algorithm>
#include <limits>

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 1920; //(1920) //formerly 800 //don't set to 0!
  unsigned const image_height = 1080; //(1200) //formerly 600 //don't set to 0!
  std::string const filename = "./rendered_image.ppm";

  //read sdf file
  Scene scene_{ read_sdf_file("./example.sdf") };

  std::vector<Ray> rays; //stores all rays in order of their pixels (top left to bottom right
  //std::vector<

  std::vector<Color> colors; //only temporary, so that I can see something

  //use default camera position (0, 0, 0)
  glm::vec3 origin{ -((image_height-1)/2.0), (image_width-1)/2.0, (image_height-1)/2.0 };

  for (int current_row = image_height-1; current_row >= 0; --current_row) //don't make int unsigned, will never go below 0
  {
      for (int current_column = image_width-1; current_column >= 0; --current_column)
      {
          //std::cout << "(" << 0 - origin[0] << ", " << current_column - origin[1] << ", " << current_row - origin[2] << ")" << "\n";
          rays.push_back(Ray{ { 0, 0, 0 }, glm::vec3{ 0, current_column, current_row } - origin });
      }
  }

  //intersect all rays with all objects...
  for (Ray const& ray : rays)
  {
      HitPoint min_distance_hitpoint{ false, std::numeric_limits<float>::max() };
      for (std::shared_ptr<Shape> shape : scene_.shapes)
      {
          HitPoint hitpoint{ shape->intersect(ray) };
          if (hitpoint.did_intersect_ && hitpoint.distance_ < min_distance_hitpoint.distance_) //...and remember the closest hitpoint
          {
              min_distance_hitpoint = hitpoint;
          }
      }
      if (min_distance_hitpoint.did_intersect_ == true) //if we did find a closer one...
      {
          colors.push_back(min_distance_hitpoint.object_material_->ka); //...remember the material information
      }
      else
      {
          colors.push_back({ 0.25, 0.25, 0.25 }); //otherwise, use the background color (a placeholder grey so far)
      }
  }/*
  for (int i = 0; i < rays.size(); ++i)
  {
      colors.push_back({ (rays[i]).direction[0], (rays[i]).direction[1], (rays[i]).direction[2] });
  }*/

  //save each pixels information into a ppm file

  //create the following renderer with a different ppm file (hopefully that's it)
  Renderer renderer{image_width, image_height, filename};

  renderer.render();

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    //window.show(renderer.color_buffer());
    window.show(colors);
  }

  return 0;
}
