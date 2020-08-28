#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 500;
  unsigned const image_height = 500;
  //std::string const filename = "./checkerboard.ppm";
  std::string const filename = "../../res/scene01.sdf";

  Renderer renderer{image_width, image_height, filename};
  Scene scene = renderer.readScene(filename);

  renderer.render(scene);

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
