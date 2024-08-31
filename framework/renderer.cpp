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
      //make the following into a function
      HitPoint min_distance_hitpoint{ false, std::numeric_limits<float>::max() };
      Ray ray{ rays[position] };
      for (auto [name, shape] : scene_.shapes)
      {
          HitPoint hitpoint{ shape->intersect(ray) };
          if (hitpoint.did_intersect_ && hitpoint.distance_ < min_distance_hitpoint.distance_) //...and remember the closest hitpoint
          {
              //move the hitpoint back a bit by the surface_normal, if shadow acne, check out get_surface_normal in Box and Sphere
              hitpoint.position_ = hitpoint.position_ + 0.0001f * shape->get_surface_normal(hitpoint);
              min_distance_hitpoint = hitpoint;
          }
      }

      //write the calculated color as a pixel
      Pixel pixel{ position % width_, position / width_ };
      if (min_distance_hitpoint.did_intersect_) //if we did intersect an object
      {
          //see if there is an obstacle inbetween the hitpoint and the light source
          HitPoint closest_obstacle{ false, std::numeric_limits<float>::max() };
          //the following only works for one light source + find a good way to calculate color
          for (Light light : scene_.lights)
          {
              //get the path to a lightsource
              Ray path{ min_distance_hitpoint.position_, light.position_ - min_distance_hitpoint.position_ };
              //check if any objects are in the way
              for (auto [name, shape] : scene_.shapes)
              {
                  //remember the hitpoint
                  HitPoint obstacle{ shape->intersect(path) };
                  if (obstacle.did_intersect_ && obstacle.distance_ < closest_obstacle.distance_) //...and remember the closest hitpoint
                  {
                      closest_obstacle = obstacle;
                  }
              }
              //somehow accumulate light for this hitpoint
          }

          if (closest_obstacle.did_intersect_)
          {
              //write the parsed ambient value (so far just a placeholder)
              pixel.color = { min_distance_hitpoint.object_material_->ka[0] * 0.25f, min_distance_hitpoint.object_material_->ka[1] * 0.25f, min_distance_hitpoint.object_material_->ka[2] * 0.25f };
              write(pixel);
          }
          else
          {
              pixel.color = min_distance_hitpoint.object_material_->ka; //remember its color...
              write(pixel); //...and write it into the color_buffer_ and ppm_file
          }
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
