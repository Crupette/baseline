#include "client/renderobject.h"

#include <glm/gtc/matrix_transform.hpp>

namespace baseline {

RenderObject::RenderObject(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale, Mesh *mesh) :
            transform_(1), update_(true), position_(position), rotation_(rotation), scale_(scale), mesh_(mesh){

}

RenderObject::~RenderObject(){

}

void RenderObject::render(ShaderProgram *program, Camera *camera){
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
    if(mesh_->getType() & MESH_INDEXED){
        
    }else{
        glDrawArrays(GL_TRIANGLES, 0, mesh_->getVertexCount());
    }
}

}
