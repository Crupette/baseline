#ifndef CAMERA_H
#define CAMERA_H 1
#ifndef SERVERSIDE

#include "shaderprogram.h"

#include <glm/glm.hpp>

namespace baseline {

class Camera {
    glm::mat4 view_;
    glm::mat4 projection_;
public:
    glm::vec3 position;
    glm::vec3 rotation;

    Camera(const glm::vec3 &position, const glm::vec3 &rotation, const glm::ivec2 windim, float near, float far, float fov);
    ~Camera();

    void update(ShaderProgram *program);
};

}

#endif
#endif
