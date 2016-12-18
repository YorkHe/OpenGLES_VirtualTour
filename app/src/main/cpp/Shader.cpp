//
// Created by 宇 on 2016/12/15.
//

#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::badbit);

        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    const GLchar* vertexShaderCode = vertexCode.c_str();
    const GLchar* fragmentShaderCode = fragmentCode.c_str();


    GLchar infoLog[512];

    mProgram = glCreateProgram();
    if (0 == mProgram){
        LOGI(1, "Create program Error");
        return;
    }

    GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);
    glLinkProgram(mProgram);
    GLint linkStatus;

    glGetProgramiv(mProgram, GL_LINK_STATUS, &linkStatus);
    if (0 == linkStatus){
        glGetProgramInfoLog(mProgram, 512, NULL, infoLog);
        glDeleteProgram(mProgram);
        LOGI(1, "ERROR::SHADER::PROGRAM::LINKING_FAILED");
//        LOGI(1, infoLog);
        return;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

GLuint Shader::compileShader(GLenum type, const char *shaderCode) {

    GLchar infoLog[512];

    GLuint shader = glCreateShader(type);
    if (0 == shader){
        LOGI(1, "Create Shader Error");
        return 0;
    }

    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOGI(1, "ERROR::SHADER::COMPILE_FAILED\n");
        LOGI(1, "infoLog: %s", infoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLint Shader::getProgram() {
    return mProgram;
}

void Shader::use() {
    glUseProgram(mProgram);
}