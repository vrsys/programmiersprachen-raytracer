#include "light.hpp"

Light::Light() :
	name_{ "unspecified_light" },
	pos_{ glm::vec3{0,0,0} },
	color_{ Color {1,1,1} },
	brightness_{ 50 }{}

Light::Light(std::string name, glm::vec3 pos, Color color, float brightness):
name_ { name },
pos_{ pos },
color_{ color },
brightness_{ brightness }{}

