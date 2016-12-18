//
// Created by 宇 on 2016/12/15.
//

#include <jni.h>
#include <cstdio>

#include <android/native_activity.h>
#include <linux/fs.h>
#include <fcntl.h>
#include <errno.h>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <SOIL/SOIL.h>

#define MOVE_PRESS 0
#define MOVE_RELEASE 1

Shader* shader;
Shader* lightShader;
Camera camera;
GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint texture;

glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;

glm::vec3 PLPosition;
glm::vec3 PLAmbient;
glm::vec3 PLDiffuse;
glm::vec3 PLSpecular;

glm::vec3 DLDirection;
glm::vec3 DLAmbient;
glm::vec3 DLDiffuse;
glm::vec3 DLSpecular;

glm::vec3 NanoPosition;
glm::vec3 NanoScale;
bool NanoRotate;

glm::vec3 STPosition;
glm::vec3 STScale;
bool STRotate;


Model* statue;
Model* nanosuit;

double angle;
long lastTime = 0;

GLfloat cube_vertices[] = {
        // Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

GLuint lightVAO, lightVBO;

extern "C"{
JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeInit(JNIEnv *env, jclass type)
{
    LOGI(1, "NATIVE LOADED");
    shader = new Shader("/sdcard/opengles/vshader.glsl", "/sdcard/opengles/fshader.glsl");
    lightShader = new Shader("/sdcard/opengles/vshader.glsl", "/sdcard/opengles/light_fshader.glsl");
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    statue = new Model("/sdcard/opengles/libertyStatue/LibertStatue.obj");
    nanosuit = new Model("/sdcard/opengles/nanosuit/nanosuit.obj");

    glGenVertexArrays(1,&lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);


    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

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

    glBindTexture(GL_TEXTURE_2D, texture);

    shader->use();

    angle += 0.001;

    model = glm::mat4(1.0f);
    model = glm::scale(model, STScale);
    model = glm::translate(model, STPosition);

    view = camera.GetViewMatrix();

    glUniform3f(glGetUniformLocation(shader->getProgram(), "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "dirLight.direction"), DLDirection.x, DLDirection.y, DLDirection.z);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "dirLight.ambient"), DLAmbient.r, DLAmbient.g, DLAmbient.b);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "dirLight.diffuse"), DLDiffuse.r, DLDiffuse.g, DLDiffuse.b);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "dirLight.specular"),DLSpecular.r, DLSpecular.g, DLSpecular.b);

    glUniform3f(glGetUniformLocation(shader->getProgram(), "pointLight.position"),  PLPosition.x, PLPosition.y, PLPosition.z);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "pointLight.ambient"),   PLAmbient.r, PLAmbient.g, PLAmbient.b);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "pointLight.diffuse"),   PLDiffuse.r, PLDiffuse.g, PLDiffuse.b);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "pointLight.specular"),  PLSpecular.r, PLSpecular.g, PLSpecular.b);
    glUniform1f(glGetUniformLocation(shader->getProgram(), "pointLight.constant"),  1.0f);
    glUniform1f(glGetUniformLocation(shader->getProgram(), "pointLight.linear"),    0.09);
    glUniform1f(glGetUniformLocation(shader->getProgram(), "pointLight.quadratic"), 0.032);


    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    statue->Draw(*shader);

    model = glm::mat4(1.0f);
    model = glm::scale(model, NanoScale);
    model = glm::translate(model, NanoPosition);


    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    nanosuit->Draw(*shader);

    lightShader->use();
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    model = glm::translate(model, PLPosition);

    glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(lightShader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
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

JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeSetPointLight(JNIEnv *env, jclass type,
                                                                 jfloat positionX, jfloat positionY, jfloat positionZ,
                                                                 jfloat ambientR, jfloat ambientG, jfloat ambientB,
                                                                 jfloat diffuseR, jfloat diffuseG, jfloat diffuseB,
                                                                 jfloat specularR, jfloat specularG, jfloat specularB){
    PLPosition.x = positionX;
    PLPosition.y = positionY;
    PLPosition.z = positionZ;

    PLAmbient.r = ambientR;
    PLAmbient.g = ambientG;
    PLAmbient.b = ambientB;

    PLDiffuse.r = diffuseR;
    PLDiffuse.g = diffuseG;
    PLDiffuse.b = diffuseB;

    PLSpecular.r = specularR;
    PLSpecular.g = specularG;
    PLSpecular.b = specularB;
}

JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeSetDirLight(JNIEnv *env, jclass type,
                                                                 jfloat directionX, jfloat directionY, jfloat directionZ,
                                                                 jfloat ambientR, jfloat ambientG, jfloat ambientB,
                                                                 jfloat diffuseR, jfloat diffuseG, jfloat diffuseB,
                                                                 jfloat specularR, jfloat specularG, jfloat specularB){
    DLDirection.x = directionX;
    DLDirection.y = directionY;
    DLDirection.z = directionZ;

    DLAmbient.r = ambientR;
    DLAmbient.g = ambientG;
    DLAmbient.b = ambientB;

    DLDiffuse.r = diffuseR;
    DLDiffuse.g = diffuseG;
    DLDiffuse.b = diffuseB;

    DLSpecular.r = specularR;
    DLSpecular.g = specularG;
    DLSpecular.b = specularB;

}

JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeSetNano(JNIEnv *env, jclass type,
                                                           jfloat positionX, jfloat positionY, jfloat positionZ,
                                                           jfloat scaleX, jfloat scaleY, jfloat scaleZ,
                                                           jboolean rotate)
{
    NanoPosition.x = positionX;
    NanoPosition.y = positionY;
    NanoPosition.z = positionZ;
    
    NanoScale.x = scaleX;
    NanoScale.y = scaleY;
    NanoScale.z = scaleZ;
    
    NanoRotate = rotate;
}


JNIEXPORT void JNICALL
Java_com_york42_esvirtualtour_CustomRenderer_nativeSetST(JNIEnv *env, jclass type,
                                                           jfloat positionX, jfloat positionY, jfloat positionZ,
                                                           jfloat scaleX, jfloat scaleY, jfloat scaleZ,
                                                           jboolean rotate)
{
    STPosition.x = positionX;
    STPosition.y = positionY;
    STPosition.z = positionZ;
    
    STScale.x = scaleX;
    STScale.y = scaleY;
    STScale.z = scaleZ;
    
    STRotate = rotate;
}


}

