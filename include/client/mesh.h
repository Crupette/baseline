#ifndef MESH_H
#define MESH_H 1
#ifndef SERVERSIDE

#include <GL/glew.h>

namespace baseline {

#define MESH_POSITIONS  0x1
#define MESH_COLORS     0x2
#define MESH_TEXTURES   0x4
#define MESH_NORMALS    0x8
#define MESH_INDEXED    0x10

class Mesh {
    uint8_t type_ = 0;
    GLuint vao_ = 0;
    size_t vertexCount_ = 0;
public:
    //Creates a new blank VAO object and binds it.
    Mesh(uint8_t type, size_t vertexCount) :
        type_(type),
        vertexCount_(vertexCount){
        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);
    }
    ~Mesh(){
        glDeleteVertexArrays(1, &vao_);
    }

    void useVAO() { glBindVertexArray(vao_); }
    size_t getVertexCount() { return vertexCount_; }
    uint8_t getType() { return type_; }
};

}

#endif
#endif
