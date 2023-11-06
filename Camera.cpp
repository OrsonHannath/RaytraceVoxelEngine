//
// Created by User on 5/07/2023.
//

#include "Camera.h"

Camera::Camera(vec3 position_, GLFWwindow* window_) {

    window = window_;
    position = position_;

    float deltT = 0;
    UpdateCamera(&deltT);
}

Camera::Camera(vec3 position_, float speed_, float mouseSpeed_, GLFWwindow *window_) {

    position = position_;
    speed = speed_;
    mouseSpeed = mouseSpeed_;
    window = window_;

    float deltT = 0;
    UpdateCamera(&deltT);
}

void Camera::UpdateCamera(float* deltaTimePtr) {

    // Get the current window size
    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    // Only update the camera if the window is focused
    if(!glfwGetWindowAttrib(window, GLFW_FOCUSED)){

        windowUnfocused = true;
        return;
    }

    // Simple way to ensure camera only updates when window is focused
    if(windowUnfocused){

        glfwSetCursorPos(window, windowWidth/2.0, windowHeight/2.0);
        windowUnfocused = false;
        return;
    }

    // If it is the initial time focusing first move cursor to centre then update the values
    double mouseX, mouseY;
    if(initialFocus){

        glfwSetCursorPos(window, windowWidth/2.0, windowHeight/2.0);
        initialFocus = false;
    }

    // Update the mouse position variables
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Reset mouse position for next frame
    glfwSetCursorPos(window, windowWidth/2.0, windowHeight/2.0);

    // Compute new orientation
    horizontalAngle += (mouseSpeed / 500) * float(windowWidth/2 - mouseX);
    verticalAngle += (mouseSpeed / 500) * float(windowHeight/2 - mouseY);

    // Direction: Spherical coordinates to Cartesian coordinates conversion
    direction = glm::vec3(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    right = glm::vec3(
            sin(horizontalAngle - glm::radians(90.0)), // Calculate perpendicular to the direction vector
            0,
            cos(horizontalAngle - glm::radians(90.0))
    );

    // Up vector: Cross product between direction and right vectors
    up = glm::cross(right, direction);

    // Normalize the vectors
    direction = glm::normalize(direction);
    right = glm::normalize(right);
    up = glm::normalize(up);

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        position += direction * *deltaTimePtr * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        position -= direction * *deltaTimePtr * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        position += right * *deltaTimePtr * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        position -= right * *deltaTimePtr * speed;
    }

    //std::cout << position.x << ", " << position.y << ", " << position.z << std::endl;
    //std::cout << direction.x << ", " << direction.y << ", " << direction.z << std::endl;
}

void Camera::SetPosition(vec3 pos) {

    position = pos;
}

void Camera::SetHorizontalAngle(float horizontalAngle_) {

    horizontalAngle = horizontalAngle_;
}

void Camera::SetVerticalAngle(float verticalAngle_) {

    verticalAngle = verticalAngle_;
}

void Camera::SetSpeed(float speed_) {

    speed = speed_;
}

void Camera::SetMouseSpeed(float mouseSpeed_) {

    mouseSpeed = mouseSpeed_;
}

vec3 Camera::GetPosition() {

    return position;
}

vec3 Camera::GetDirection() {

    return direction;
}

vec3 Camera::GetRight() {

    return right;
}

vec3 Camera::GetUp() {

    return up;
}

GLFWwindow* Camera::GetWindow() {

    return window;
}

void Camera::SetFOV(float fov_) {
    fov = fov_;
}

float Camera::GetFOV() {
    return fov;
}
