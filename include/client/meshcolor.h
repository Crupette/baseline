#ifndef MESH_COLOR_H
#define MESH_COLOR_H 1
#ifndef SERVERSIDE

#include "mesh.h"

namespace baseline {

class MeshColor : public Mesh<2> {
    int vertCount_;
public:
    MeshColor(const std::vector<float> &positions, const std::vector<unsigned char> &colors);
    ~MeshColor() {}

    int getVertexCount();
};

}

#endif
#endif
