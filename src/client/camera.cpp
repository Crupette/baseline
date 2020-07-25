#include "client/camera.h"
#include "client/base.h"

#include <glm/gtc/matrix_transform.hpp>

namespace baseline {

Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, float near, float far, float fov) :
    view_(1), projection_(1), position(position), rotation(rotation), nearplane_(near), farplane_(far), fov_(fov){
}

Camera::~Camera(){

}

void Camera::update(ShaderProgram *program){
    view_ = glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0));
    view_ = glm::rotate(view_, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    view_ = glm::rotate(view_, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    view_ = glm::translate(view_, position);

    glm::ivec2 windim = BaseClient::window->getSize();
    projection_ = glm::perspective(glm::radians(fov_), (float)windim.x / (float)windim.y, nearplane_, farplane_);

    glUniformMatrix4fv(program->getUniform("projectionMatrix"), 1, GL_FALSE, &(projection_[0][0]));
    glUniformMatrix4fv(program->getUniform("viewMatrix"), 1, GL_FALSE, &(view_[0][0]));
}

}
