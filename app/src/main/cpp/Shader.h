//
// Created by 宇 on 2016/12/15.
//

#pragma once

#include <GLES3/gl3.h>
#include <android/log.h>

#define LOGI(level, ...) __android_log_print(ANDROID_LOG_INFO, "NATIVE_LOG", __VA_ARGS__)

class Shader{

public:
    Shader(const char *vertexShaderCode, const char *fragmentShaderCode);
    GLint getProgram();
    void use();

private:
    GLuint compileShader(GLenum type, const char* shaderCode);
    GLuint mProgram;
    GLint mShader;
};


