//
// Created by User on 17/04/2023.
//

#include "TestingShaderProgramHandler.h"
TestingShaderProgramHandler::TestingShaderProgramHandler(){

    // Create and add the main program
    std::vector<std::string> mainProgramShaders = {"../shaders/VertexShader.vertshader", "../shaders/FragmentShader.fragshader"};
    ShaderProgram* mainProgram = new ShaderProgram("MainProgram", mainProgramShaders);
    AddProgram(mainProgram);

    // Create and add the raytrace compute program
    std::vector<std::string> raycastProgramShaders = {"../shaders/VoxelRaycastComputeShader.compshader"};
    ShaderProgram* raytraceProgram = new ShaderProgram("RaytraceProgram", raycastProgramShaders);
    AddProgram(raytraceProgram);
}