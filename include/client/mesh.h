#ifndef MESH_H
#define MESH_H 1
#ifndef SERVERSIDE

#include <vector>
#include <cstdio>

#include <GL/glew.h>

namespace baseline {

struct AttribDescriptor {
    unsigned char elementCount;
    GLenum dt;
    bool normalize;
};

template<int N=1>
class Mesh {
    int next_attrib_ = 0;
protected:
    GLuint vao_;
    GLuint vbo_[N];

    //TODO: Figure out how to pass vector by reference
    template<typename T>
    void addVBO(int attr, const AttribDescriptor &descriptor, std::vector<T> data){
        glBindBuffer(GL_ARRAY_BUFFER, vbo_[attr]);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(attr);
        glVertexAttribPointer(attr, descriptor.elementCount, descriptor.dt, descriptor.normalize, 0, NULL);

        next_attrib_++;
    }
public:
    template<typename ...Ts>
    Mesh(std::vector<AttribDescriptor> descriptors, Ts (&...data)){
        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glGenBuffers(N, vbo_);

        ((addVBO(next_attrib_, descriptors[next_attrib_], data)), ...);
    }

    ~Mesh(){
        glDeleteVertexArrays(1, &vao_);
        glDeleteBuffers(N, vbo_);
    }

    void useVao(){ glBindVertexArray(vao_); }
    virtual int getVertexCount() = 0;
};

}

#endif
#endif
