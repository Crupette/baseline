#include "client/meshraw.h"

#include <cstdio>

namespace baseline {

MeshRaw::MeshRaw(const std::vector<float> &positions) 
    : Mesh(
            std::vector<AttribDescriptor> {
                {3, GL_FLOAT, false}
            },
            positions) {
    vertCount_ = positions.size();
}

int MeshRaw::getVertexCount(){
    return vertCount_;
}

}
