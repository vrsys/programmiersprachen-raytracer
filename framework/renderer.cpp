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

      glm::vec3 intersected_shape_surface_normal;

      Ray ray{ rays[position] };

      //write the calculated color as a pixel
      Pixel pixel{ position % width_, position / width_ };

      for (auto const& [name, shape] : scene_.shapes)
      {
          HitPoint hitpoint{ shape->intersect(ray) };
          if (hitpoint.did_intersect_ && hitpoint.distance_ < min_distance_hitpoint.distance_) //...and remember the closest hitpoint
          {
              intersected_shape_surface_normal = shape->get_surface_normal(hitpoint);
              //move the hitpoint back a bit by the surface_normal, if shadow acne, check out get_surface_normal in Box and Sphere
              hitpoint.position_ = hitpoint.position_ + 0.0001f * intersected_shape_surface_normal;
              min_distance_hitpoint = hitpoint;
          }
      }

      if (min_distance_hitpoint.did_intersect_) //if we did intersect an object
      {
          //see if there is an obstacle inbetween the hitpoint and the light source
          HitPoint closest_obstacle{ false, std::numeric_limits<float>::max() };
          //accumulate light from every visible light source
          for (int i = 0; i < 3; ++i)
          {
              pixel.color[i] = 0.1f * min_distance_hitpoint.object_material_->ka[i]; //this is the ambient part
          }
          for (Light const& light : scene_.lights)
          {
              bool light_visibility = 1;
              //get the path to a lightsource
              Ray path{ min_distance_hitpoint.position_, light.position_ - min_distance_hitpoint.position_ };
              //check if any objects are in the way
              for (auto const& [name, shape] : scene_.shapes)
              {
                  //remember the hitpoint
                  HitPoint obstacle{ shape->intersect(path) };
                  if (obstacle.did_intersect_ && obstacle.distance_ < closest_obstacle.distance_) //...and remember the closest hitpoint
                  {
                      closest_obstacle = obstacle;
                      light_visibility = 0; //if there is an object in the way, this term nullifies diffuse and specular reflections
                  }
              }
              //light_visibility * (brightness of light source) * (kd * path_to_light_source * surface_normal
              // + ks * (reflected/outgoing ray * the ray from the hitpoint to the cameras eye))
              glm::vec3 reflected = -2 * glm::dot(path.direction, intersected_shape_surface_normal) * intersected_shape_surface_normal + path.direction;
              reflected = glm::normalize(reflected);
              for (int i = 0; i < 3; ++i)
              {
                  pixel.color[i] += light_visibility * light.brightness_ * (min_distance_hitpoint.object_material_->kd[i]
                      * (std::max(glm::dot(path.direction, intersected_shape_surface_normal), 0.0f))
                      + min_distance_hitpoint.object_material_->ks[i]
                      * std::pow(std::max(glm::dot(reflected, ray.direction), 0.0f), min_distance_hitpoint.object_material_->exponent));
              }
          }
          //surface_normal visualisation
          //for (int i = 0; i < 3; ++i)
          //{
          //    pixel.color[i] = /*std::abs(*/intersected_shape_surface_normal[i]/*)*/;
          //}
          write(pixel);
      }
      else //if no object is hit
      {
          pixel.color = { 0.25, 0.25, 0.25 }; //this should be some sort of background image (or the ambient color value?)
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
