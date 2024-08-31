// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
  //read sdf file
  Scene scene_{ read_sdf_file("./example.sdf") };

  Camera test_camera{ "test_camera", std::numbers::pi / 2.0, { 0, 0, 0 }, { 0, 0, -1 }, { 0, 1, 0 } };
  std::cout << test_camera;

  std::vector<Ray> rays{ test_camera.generate_rays(width_, height_) }; //returns all rays in order of their pixels (top left to bottom right)

  //intersect all rays with all objects...
  for (int position = 0; position < rays.size(); ++position)
  {
      HitPoint min_distance_hitpoint{ false, std::numeric_limits<float>::max() };
      Ray ray{ rays[position] };
      for (std::shared_ptr<Shape> shape : scene_.shapes)
      {
          HitPoint hitpoint{ shape->intersect(ray) };
          if (hitpoint.did_intersect_ && hitpoint.distance_ < min_distance_hitpoint.distance_) //...and remember the closest hitpoint
          {
              min_distance_hitpoint = hitpoint;
          }
      }
      Pixel pixel{ position % width_, position / width_ };
      if (min_distance_hitpoint.did_intersect_ == true) //if we did find a closer one...
      {
          pixel.color = min_distance_hitpoint.object_material_->ka; //remember its color...
          write(pixel); //...and write it into the color_buffer_ and ppm_file
      }
      else
      {
          pixel.color = { 0.25, 0.25, 0.25 };
          write(pixel);
      }
  }
  ppm_.save(filename_); //writes everything out of ppm_.data_ into a ppm file
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
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
