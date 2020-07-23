#include "client/meshraw.h"


namespace baseline {

MeshRaw::MeshRaw(const std::vector<float> &positions) : 
    Mesh(MESH_POSITIONS, positions.size()) {
    glGenBuffers(1, &vbo_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

MeshRaw::~MeshRaw(){
    glDeleteBuffers(1, &vbo_);
}

}
