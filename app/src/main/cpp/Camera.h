//
// Created by 宇 on 2016/12/15.
//

#ifndef ESVIRTUALTOUR_CAMERA_H
#define ESVIRTUALTOUR_CAMERA_H

#include <GLES3/gl3.h>
#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    DOWN,
    UP
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 0.0009f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera{
public:
    bool keys[1024];
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    GLfloat Yaw;
    GLfloat Pitch;

    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;
    bool firstMouse;

    GLfloat lastX;
    GLfloat lastY;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

    glm::mat4 GetViewMatrix();

    void doMovement(long deltaTime);
    void onMovePress(int movement);
    void onMoveRelease(int movement);
    void onViewMovement(float xOffset, float yOffset);

private:
    GLfloat currentFrame;
    GLfloat lastFrame;
    GLfloat deltaTime;

    void updateCameraVectors();
    void processMovement(int movement, long deltaTime);
};

#endif //ESVIRTUALTOUR_CAMERA_H
