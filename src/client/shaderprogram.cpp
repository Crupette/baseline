#include "client/shaderprogram.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace baseline {

ShaderProgram::ShaderProgram() : program_(0), linked_(false){
    program_ = glCreateProgram();
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(program_);
}

void ShaderProgram::addShader(Shader shader){
    if(linked_) return;
    GLuint shaderId = glCreateShader(shader.type);

    std::string code;
    std::ifstream shaderstream(shader.path, std::ios::in);

    GLint res = GL_FALSE;
    int loglen = 0;

    if(shaderstream.fail()){
        printf("Missing shader file: %s. May make things worse / crash the program. Good luck!\n", shader.path.c_str());
        return;
    }

    std::stringstream ss;
    ss << shaderstream.rdbuf();
    code = ss.str();
    shaderstream.close();

    char const *srcptr = code.c_str();
    glShaderSource(shaderId, 1, &srcptr, 0);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &res);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &loglen);
    if(loglen > 0){
        std::vector<char> errmsg(loglen + 1);
        glGetShaderInfoLog(shaderId, loglen, NULL, &errmsg[0]);
        printf("%s\n", &errmsg[0]);
    }

    glAttachShader(program_, shaderId);
    compiledShaders_.push_back(shaderId);
}

void ShaderProgram::link(){
    GLint res = GL_FALSE;
    int loglen = 0;

    linked_ = true;
    glLinkProgram(program_);

    glGetProgramiv(program_, GL_COMPILE_STATUS, &res);
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &loglen);
    if(loglen > 0){
        std::vector<char> errmsg(loglen + 1);
        glGetProgramInfoLog(program_, loglen, NULL, &errmsg[0]);
        printf("%s\n", &errmsg[0]);
    }

    for(GLuint id : compiledShaders_){
        glDetachShader(program_, id);
    }
}

}
