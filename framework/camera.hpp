#include <glm/vec3.hpp>
#include <string>


class Camera {

  public:
       Camera();
       Camera(std::string const& name ,glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& right, glm::vec3 const& down);


       

   private:
       std::string name_ = "Camera";
       glm::vec3 campos;
       glm::vec3 camdir;
       glm::vec3 camright;
       glm::vec3 camdown;
};