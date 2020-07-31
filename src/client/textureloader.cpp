#include "client/textureloader.h"
#include "client/lodepng.h"

#include <vector>
#include <sstream>
#include <iostream>

namespace baseline {

std::unordered_map<std::string, std::shared_ptr<Texture>> TextureLoader::cache_;

void getDataFromPNG(const std::string &path, std::vector<unsigned char> &data, int &w, int &h){
    std::vector<unsigned char> filedata;
    unsigned width, height;

    unsigned err = lodepng::load_file(filedata, path.c_str());
    if(!err) err = lodepng::decode(data, width, height, filedata);

    if(err) printf("decode error %i : %s\n", err, lodepng_error_text(err));

    w = width;
    h = height;
}

Texture *loadTexture(const std::string &path){
    Texture *texture = new Texture();
    std::vector<unsigned char> texData;

    getDataFromPNG(path, texData, texture->width, texture->height);

    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texData[0]);

    return texture;
}

Texture::Texture(){
    glGenTextures(1, &id);
}

Texture::~Texture(){
    glDeleteTextures(1, &id);
}

std::shared_ptr<Texture> TextureLoader::getTexture(const std::string &path){
    auto it = cache_.find(path);

    if(it == cache_.end()){
        std::shared_ptr<Texture> texture = std::unique_ptr<Texture>(loadTexture(path));
        cache_.emplace(path, texture);
        return texture;
    }else{
        return it->second;
    }
}

}
