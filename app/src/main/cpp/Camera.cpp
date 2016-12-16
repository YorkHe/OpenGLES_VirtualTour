//
// Created by 宇 on 2016/12/15.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Camera.h"

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ,
               GLfloat yaw, GLfloat pitch):Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY),Zoom(ZOOM)
{

    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp = glm::vec3(upX, upY, upZ);
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch):Front(glm::vec3(0.0f, 0.0f, -1.0f)),MovementSpeed(SPEED),MouseSensitivity(SENSITIVITY),Zoom(ZOOM){
    this->Position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));

    this->Front = glm::normalize(front);
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
    this->Up = glm::normalize(glm::cross(this->Right, this->Front));

}


void Camera::processMovement(int movement, long deltaTime) {

    GLfloat velocity = this->MovementSpeed * deltaTime;

    switch(movement)
    {
        case FORWARD:
            this->Position += this->Front * velocity;
            break;
        case BACKWARD:
            this->Position -= this->Front * velocity;
            break;
        case LEFT:
            this->Position -= this->Right * velocity;
            break;
        case RIGHT:
            this->Position += this->Right * velocity;
            break;
        default:
            break;
    }
}

void Camera::doMovement(long deltaTime) {
    if (keys[FORWARD] == GL_TRUE)
        processMovement(FORWARD, deltaTime);
    if (keys[BACKWARD] == GL_TRUE)
        processMovement(BACKWARD, deltaTime);
    if (keys[LEFT] == GL_TRUE)
        processMovement(LEFT, deltaTime);
    if (keys[RIGHT] == GL_TRUE)
        processMovement(RIGHT, deltaTime);
}

void Camera::onMovePress(int movement) {
    LOGI(1, "%d", movement);
    keys[movement] = GL_TRUE;
}

void Camera::onMoveRelease(int movement) {
    keys[movement] = GL_FALSE;
}

void Camera::onViewMovement(float xOffset, float yOffset) {
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw += xOffset;
    Pitch += yOffset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    updateCameraVectors();
}