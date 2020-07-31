#ifndef MESH_RAW_H
#define MESH_RAW_H 1
#ifndef SERVERSIDE

#include <vector>
#include "mesh.h"

namespace baseline {

class MeshRaw : public Mesh<1> {
    int vertCount_;
public:
    MeshRaw(const std::vector<float> &positions);
    ~MeshRaw() {}

    virtual int getVertexCount();
};

}

#endif
#endif
