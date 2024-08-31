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
  unsigned const image_height = 1200; //(1200) //formerly 600 //don't set to 0!
  std::string const filename = "./rendered_image.ppm";

  Renderer renderer{image_width, image_height, filename};

  renderer.render();

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
