//
// Created by User on 23/03/2023.
//

#ifndef ADVANCEDVOXELENGINE_OPENGLAPP_H
#define ADVANCEDVOXELENGINE_OPENGLAPP_H

#include <iostream>
#include <cstdio>
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "SceneManager.h"
#include "Scene.h"
#include "assets/scenes/VoxelWorldScene.h"
#include "ShaderProgram.h"
#include "ShaderProgramHandler.h"
#include "TestingShaderProgramHandler.h"
#include "DeltaTime/DeltaTime.h"

class OpenGLApp {
public:
    OpenGLApp();

    int OnExecute(int width, int height);
    bool OnInit();
    void OnLoop();
    void OnRender();
    void OnExit();

    GLuint* LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* compute_file_path);

private:

    // Window Settings
    GLFWwindow* window;
    int wWidth;
    int wHeight;

    // Time management
    float deltaTime;
    double time_;

    // Scene management
    SceneManager* sceneManager;

    // Shader handling
    ShaderProgramHandler* shaderProgramHandler;
};


#endif //ADVANCEDVOXELENGINE_OPENGLAPP_H
