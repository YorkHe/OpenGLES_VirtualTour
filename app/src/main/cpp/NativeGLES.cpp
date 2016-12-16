//
// Created by 宇 on 2016/12/15.
//

#include <jni.h>

#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#define MOVE_PRESS 0
#define MOVE_RELEASE 1

Shader* shader;
Camera camera;
GLuint VBO;
GLuint VAO;

glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;

double angle;
long lastTime = 0;

GLfloat VERTEX[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end

        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end

        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,

        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,

        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,

        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,

        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
};

extern "C"{
JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeInit(JNIEnv *env, jclass type, jstring vertexShaderSource, jstring fragmentShaderSource)
{
    const char *vertexShaderCode = env->GetStringUTFChars(vertexShaderSource, 0);
    const char *fragmentShaderCode = env->GetStringUTFChars(fragmentShaderSource, 0);
    LOGI(1, "NATIVE LOADED");
    shader = new Shader(vertexShaderCode, fragmentShaderCode);
    env->ReleaseStringUTFChars(vertexShaderSource, vertexShaderCode);
    env->ReleaseStringUTFChars(fragmentShaderSource, fragmentShaderCode);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    LOGI(1, "SHADER CREATED");
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    LOGI(1, "BUFFER CREATED");

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX), VERTEX, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    LOGI(1, "BUFFER ATTRIB CREATED");
}

JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeDraw(JNIEnv *env, jclass type, long currentTime)
{
    long deltaTime = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (lastTime != 0)
        deltaTime = currentTime - lastTime;
    else
        deltaTime = 0;

    lastTime = currentTime;

    camera.doMovement(deltaTime);


    shader->use();

    angle += 0.001;

    model = glm::mat4(1.0f);
//    model = glm::rotate(model, angleX, glm::vec3(1,0,0));
//    model = glm::rotate(model, angleY, glm::vec3(0,1,0));
    view = camera.GetViewMatrix();

    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
    glBindVertexArray(0);
}

JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeSurfaceChanged(JNIEnv *env, jclass type, jint width, jint height)
{
    projection = glm::perspective(glm::radians(90.0f), (float)width/height,0.1f, 100.0f);

    glViewport(0, 0, width, height);
}

JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeDirectionCallback(JNIEnv *env, jclass type, jint direction, jint evt)
{
    LOGI(1, "PRESSED %d", evt);
    if (evt == MOVE_PRESS)
        camera.onMovePress(direction);
    else if (evt == MOVE_RELEASE)
        camera.onMoveRelease(direction);
}

JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeViewCallback(JNIEnv *env, jclass type, jfloat xOffset, jfloat yOffset)
{
    camera.onViewMovement(xOffset, yOffset);
}

}

