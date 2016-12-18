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

glm::vec3 lightPos(0.0f, 10.0f, 0.0f);

Model* statue;

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

GLfloat plane_vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f,0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f,1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f,0.0f, 0.0f
};

GLuint lightVAO, lightVBO;
GLuint planeVAO, planeVBO;

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

    glGenVertexArrays(1,&lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);


    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);



    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW);

    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

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

    view = camera.GetViewMatrix();

    glUniform3f(glGetUniformLocation(shader->getProgram(), "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "dirLight.direction"), -0.2f, -1.0f, -0.3f);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "dirLight.ambient"), 0.3f, 0.3f, 0.3f);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "dirLight.specular"), 0.5f, 0.5f, 0.5f);

    glUniform3f(glGetUniformLocation(shader->getProgram(), "pointLight.position"),  lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "pointLight.ambient"),   0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "pointLight.diffuse"),   0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(shader->getProgram(), "pointLight.specular"),  1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader->getProgram(), "pointLight.constant"),  1.0f);
    glUniform1f(glGetUniformLocation(shader->getProgram(), "pointLight.linear"),    0.09);
    glUniform1f(glGetUniformLocation(shader->getProgram(), "pointLight.quadratic"), 0.032);


    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    statue->Draw(*shader);

    lightShader->use();
    model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    model = glm::translate(model, lightPos);

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

}

