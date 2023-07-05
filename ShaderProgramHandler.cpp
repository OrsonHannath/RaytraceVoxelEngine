//
// Created by User on 17/04/2023.
//

#include "ShaderProgramHandler.h"

ShaderProgramHandler::ShaderProgramHandler(){

}

void ShaderProgramHandler::AddProgram(ShaderProgram* shaderProgram){

    programsMap[shaderProgram->GetProgramName()] = shaderProgram->GetProgramID();
}

std::map<std::string, GLuint>* ShaderProgramHandler::GetProgramMap() {

    return &programsMap;
}

GLuint ShaderProgramHandler::GetProgramID(std::string programName){

    return programsMap[programName];
}
