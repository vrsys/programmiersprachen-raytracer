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
    std::size_t const checker_pattern_size = 20;

    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            //for every pixel on our screen we need to find a ray going from origin to out 
            Ray ray = camera_ray(scene.camera, x, y);
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
        return (Color{ 0,0,0 });
    }
    else {
        return (Color{ 1,1,1 });
    }

   
    return Color {0,0,0};
    }

Ray Renderer::camera_ray(std::shared_ptr<Camera> camera, int x, int y)
{
    /*
    * We currently have a window made of pixels, we want to convert this into rays to calculate intersections
    * this aims to turn a pixel value into a vector and then a ray which goes out from camera position to 
    * essentially map out our scene seen through our window
    */
    double normalized_x = (x + 0.5) / width_;
    double normalized_y = (y + 0.5) / height_;
    double window_space_x = (2 * normalized_x - 1) * ratio_;
    double window_space_y = (1 - 2 * normalized_x);
    //double scale =
    
    glm::vec3 dir{window_space_x, window_space_y, -1};
    
    return Ray{camera->cam_pos, glm::normalize(dir)};
   
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
