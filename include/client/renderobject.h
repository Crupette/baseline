#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H 1
#ifndef SERVERSIDE

#include "mesh.h"
#include "shaderprogram.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace baseline {

template<int N>
class RenderObject {
    glm::mat4 transform_;
    bool update_;

    glm::vec3 position_, rotation_, scale_;

    Mesh<N> *mesh_;
public:
    RenderObject(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, Mesh<N> *mesh)
        : transform_(1), update_(true), position_(position), rotation_(rotation), scale_(scale), mesh_(mesh) { }

    ~RenderObject() {}

    void render(ShaderProgram *program){
        program->use();

        if(update_){
            update_ = false;
            transform_ = glm::scale(glm::mat4(1), scale_);
            transform_ = glm::rotate(transform_, rotation_.x, glm::vec3(0, 1, 0));
            transform_ = glm::rotate(transform_, rotation_.y, glm::vec3(1, 0, 0));
            transform_ = glm::rotate(transform_, rotation_.z, glm::vec3(0, 0, 1));
            transform_ = glm::translate(transform_, position_);
        }
        glUniformMatrix4fv(program->getUniform("transformationMatrix"), 1, GL_FALSE, &(transform_[0][0]));

        mesh_->useVao();
        glDrawArrays(GL_TRIANGLES, 0, mesh_->getVertexCount());
    }

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
