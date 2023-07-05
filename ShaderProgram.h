//
// Created by User on 17/04/2023.
//

#ifndef ADVANCEDVOXELENGINE_SHADERPROGRAM_H
#define ADVANCEDVOXELENGINE_SHADERPROGRAM_H

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>

class ShaderProgram {
private:
    std::string programName;
    GLuint programID;
public:
    ShaderProgram(std::string programName, std::vector<std::string> filePaths);

    GLuint GetProgramID();
    std::string GetProgramName();
};


#endif //ADVANCEDVOXELENGINE_SHADERPROGRAM_H
