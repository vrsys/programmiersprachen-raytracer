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
  std::string filename = "../../res/scene01.sdf";
  //File to write image to
  std::string renderedSceneFilename = "../../res/scene01.ppm";

  if (argc > 1) {
      filename = argv[1];
      std::cout << "filename:" << filename << std::endl;
  }
  
  if (argc > 2) {
      renderedSceneFilename = argv[2];
      std::cout << "renderedSceneFilename:" << renderedSceneFilename << std::endl;
  }

  Renderer renderer{image_width, image_height, renderedSceneFilename};
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
