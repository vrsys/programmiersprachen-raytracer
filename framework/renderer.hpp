// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"
#include "ray.hpp"

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  void render();
  void render(Scene& scene);
  Ray camera_ray(Camera const& camera, int x, int y);
  Color trace(Scene& scene, Ray& ray);
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  unsigned ratio_ = width_/height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
