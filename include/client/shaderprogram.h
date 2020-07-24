#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H 1
#ifndef SERVERSIDE

#include <string>
#include <vector>
#include <unordered_map>

#include <GL/glew.h>

namespace baseline{

struct Shader {
    GLenum type;
    std::string path;
};

class ShaderProgram {
    GLuint program_;
    std::vector<GLuint> compiledShaders_;
    std::unordered_map<std::string, GLuint> uniforms_;
    bool linked_;
public:
    ShaderProgram();
    ~ShaderProgram();

    void addShader(Shader shader);
    void link();

    void use() { glUseProgram(program_); }

    GLuint getUniform(const std::string &name);
};

}

#endif
#endif
