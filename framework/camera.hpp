#include <glm/vec3.hpp>


class Camera {

   public:
       Camera();
       Camera(glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& right, glm::vec3 const& down);


       

   private:
       glm::vec3 campos;
       glm::vec3 camdir;
       glm::vec3 camright;
       glm::vec3 camdown;
};