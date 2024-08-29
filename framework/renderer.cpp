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
  std::size_t const checker_pattern_size = 20;

  //read sdf file
  Scene scene_{ read_sdf_file("./example.sdf") };

  std::vector<Ray> rays; //stores all rays in order of their pixels (top left to bottom right

  //use default camera position (0, 0, 0)
  glm::vec3 origin{ -((height_ - 1) / 2.0), (width_ - 1) / 2.0, (height_ - 1) / 2.0 };

  for (int current_row = height_ - 1; current_row >= 0; --current_row) //don't make int unsigned, will never go below 0
  {
      for (int current_column = width_ - 1; current_column >= 0; --current_column)
      {
          //std::cout << "(" << 0 - origin[0] << ", " << current_column - origin[1] << ", " << current_row - origin[2] << ")" << "\n";
          rays.push_back(Ray{ { 0, 0, 0 }, glm::vec3{ 0, current_column, current_row } - origin });
      }
  }

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
          pixel.color = min_distance_hitpoint.object_material_->ka;
          write(pixel);
      }
      else
      {
          pixel.color = { 0.25, 0.25, 0.25 };
          write(pixel);
      }
  }

  //read from filename_ (ppm file)

  //for (unsigned y = 0; y < height_; ++y) {
  //  for (unsigned x = 0; x < width_; ++x) {
  //    Pixel p(x,y);
  //    /*if (((x / checker_pattern_size) % 2) != ((y / checker_pattern_size) % 2)) {
  //      p.color = Color{0.0f, 1.0f, float(x)/height_};
  //    } else {
  //      p.color = Color{1.0f, 0.0f, float(y)/width_};
  //    }*/
  //          
  //    p.color = Color{ float(x)/width_, 0.0f, float(y)/height_ };
  //    
  //    write(p);
  //  }
  //}
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
