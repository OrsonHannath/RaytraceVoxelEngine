//
// Created by User on 26/03/2023.
//

#ifndef ADVANCEDVOXELENGINE_SCENE_H
#define ADVANCEDVOXELENGINE_SCENE_H


#include <iostream>
#include <map>
#include <glew.h>
#include <vector>
#include <cmath>
#include <memory>
#include <glfw3.h>

class Scene {
protected:
    std::map<std::string, GLuint> GLHandles;
    GLFWwindow* window;
private:
    std::string name;
    int win_width, win_height;
    GLuint screenTex;
    GLuint VAO, VBO, EBO;

public:

    Scene(std::string name_, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_);
    virtual void UpdateScene(float* deltaTimePtr);
    virtual void RenderScene(float* deltaTimePtr);
    void SetGLHandle(std::string handleStr_, GLuint handleVal_);

    std::string GetName();
};


#endif //ADVANCEDVOXELENGINE_SCENE_H
