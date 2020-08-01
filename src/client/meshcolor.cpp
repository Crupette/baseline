#include "client/meshcolor.h"

namespace baseline {

MeshColor::MeshColor(const std::vector<float> &positions, const std::vector<unsigned char> &colors)
    : Mesh(
            std::vector<AttribDescriptor> {
                {3, GL_FLOAT, false},
                {4, GL_UNSIGNED_BYTE, true}
            },
            positions,
            colors) {
    vertCount_ = positions.size();
}

int MeshColor::getVertexCount(){
    return vertCount_;
}

}
