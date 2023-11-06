//
// Created by User on 5/07/2023.
//

#ifndef ADVANCEDVOXELENGINE_CAMERA_H
#define ADVANCEDVOXELENGINE_CAMERA_H

#include "libraries/GLFW/glfw3.h"
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

struct CameraStruct{
    float posX, posY, posZ;
    float dirX, dirY, dirZ;
    float rightX, rightY, rightZ;
    float upX, upY, upZ;
    float aspectRatio;
    float fov;
};

using namespace glm;

class Camera {
private:
    vec3 position = vec3();
    vec3 direction = vec3();
    vec3 right = vec3();
    vec3 up = vec3();

    float fov = 60.0f;
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    float speed = 25.0f;
    float mouseSpeed = 0.5f;

    GLFWwindow* window;
    bool windowUnfocused = false;
    bool initialFocus = true;
public:

    Camera(vec3 position_, GLFWwindow* window_);
    Camera(vec3 position_, float speed_, float mouseSpeed_, GLFWwindow* window_);

    void SetPosition(vec3 pos);
    void SetHorizontalAngle(float horizontalAngle_);
    void SetVerticalAngle(float verticalAngle_);
    void SetSpeed(float speed_);
    void SetMouseSpeed(float mouseSpeed_);
    void UpdateCamera(float* deltaTimePtr);

    vec3 GetPosition();
    vec3 GetDirection();
    vec3 GetRight();
    vec3 GetUp();

    void SetFOV(float fov_);
    float GetFOV();

    GLFWwindow* GetWindow();
};


#endif //ADVANCEDVOXELENGINE_CAMERA_H
