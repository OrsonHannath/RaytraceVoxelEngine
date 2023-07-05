//
// Created by User on 17/04/2023.
//

#ifndef ADVANCEDVOXELENGINE_SHADERPROGRAMHANDLER_H
#define ADVANCEDVOXELENGINE_SHADERPROGRAMHANDLER_H

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "ShaderProgram.h"

class ShaderProgramHandler {
protected:
    std::map<std::string, GLuint> programsMap;
public:
    ShaderProgramHandler();
    void AddProgram(ShaderProgram* shaderProgram);

    std::map<std::string, GLuint>* GetProgramMap();
    GLuint GetProgramID(std::string programName);
};


#endif //ADVANCEDVOXELENGINE_SHADERPROGRAMHANDLER_H
