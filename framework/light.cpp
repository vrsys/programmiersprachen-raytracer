#include "light.hpp"

Light::Light(std::string name, glm::vec3 pos, Color color, float brightness):
name_ { name },
pos_{ pos },
color_{ color },
brightness_{ brightness }{}

