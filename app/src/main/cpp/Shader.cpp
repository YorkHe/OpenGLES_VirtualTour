//
// Created by 宇 on 2016/12/15.
//

#include "Shader.h"

Shader::Shader(const char *vertexShaderCode, const char *fragmentShaderCode) {
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