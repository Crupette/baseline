#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H 1
#ifndef SERVERSIDE

#include <unordered_map>
#include <string>
#include <memory>

#include <GL/glew.h>

namespace baseline {

struct Texture {
    Texture();
    ~Texture();

    GLuint id;
    int width, height;
};

class TextureLoader {
    static std::unordered_map<std::string, std::shared_ptr<Texture>> cache_;
public:
    static std::shared_ptr<Texture> getTexture(const std::string &path);
};

}

#endif
#endif
