#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H 1
#ifndef SERVERSIDE

#include "mesh.h"
#include "shaderprogram.h"
#include "camera.h"

#include <glm/glm.hpp>

namespace baseline {

class RenderObject {
    glm::mat4 transform_;
    bool update_;

    glm::vec3 position_, rotation_, scale_;

    Mesh<> *mesh_;
public:
    RenderObject(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, Mesh<> *mesh);
    ~RenderObject();

    void render(ShaderProgram *program);

    glm::vec3 getPosition() { return position_; }
    glm::vec3 getRotation() { return rotation_; }
    glm::vec3 getScale()    { return scale_; }

    void setPosition(const glm::vec3 &to)   { update_ = true; position_ = to; }
    void setRotation(const glm::vec3 &to)   { update_ = true; rotation_ = to; }
    void setScale(const glm::vec3 &to)      { update_ = true; scale_ = to; }

    void translatePosition(const glm::vec3 &by) { setPosition(getPosition() + by); }
    void translateRotation(const glm::vec3 &by) { setRotation(getRotation() + by); }
    void translateScale(const glm::vec3 &by)    { setScale(getScale() + by); }
};

}

#endif
#endif
