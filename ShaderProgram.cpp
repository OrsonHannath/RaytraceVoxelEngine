//
// Created by User on 17/04/2023.
//
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string programName_, std::vector<std::string> filePaths) {

    std::cout << "--- Initializing Shader: " << programName_ << " ---" << std::endl;

    std::vector<GLuint> shaderIDs;
    programName = programName_;

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Loop through provided shader file paths and create shaders for them
    for(std::string filePath : filePaths) {

        GLenum shaderType;
        const char *file_path_char = filePath.c_str();

        // Firstly determine if what type of shader this should be based on filetype
        std::string fileTypeFormat = "xxxxshader";
        std::string fileType = filePath.substr(filePath.length() - fileTypeFormat.length(), filePath.length());

        if (fileType == "vertshader") {
            shaderType = GL_VERTEX_SHADER;
        } else if (fileType == "fragshader") {
            shaderType = GL_FRAGMENT_SHADER;
        } else if (fileType == "compshader") {
            shaderType = GL_COMPUTE_SHADER;
        }

        // Create the shader
        GLuint shaderID = glCreateShader(shaderType);

        // Read the shader code from specified file
        std::string shaderCode;
        std::ifstream shaderStream(file_path_char, std::ios::in);
        if (shaderStream.is_open()) {
            std::stringstream sstr;
            sstr << shaderStream.rdbuf();
            shaderCode = sstr.str();
            shaderStream.close();
        } else {
            printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n",
                   file_path_char);
            getchar();
        }

        // Compile the Shader
        printf("Compiling shader : %s\n", file_path_char);
        char const *sourcePointer = shaderCode.c_str();
        glShaderSource(shaderID, 1, &sourcePointer, NULL);
        glCompileShader(shaderID);

        // Check the Shader
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> shaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &shaderErrorMessage[0]);
            printf("%s\n", &shaderErrorMessage[0]);
        }

        // Push the shaderID to the shaderIDs vector, so they can be linked
        shaderIDs.push_back(shaderID);
    }

    // Link the program
    printf(("Linking program: " + programName + "\n").c_str());
    programID = glCreateProgram();

    // Attach the loaded shaders
    for(GLuint shaderID : shaderIDs){
        glAttachShader(programID, shaderID);
    }

    // Compile and Link the program
    //glCompileShader(programID); // This was causing error 1282
    glLinkProgram(programID);

    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &Result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    // Delete the shaders
    for(GLuint shaderID : shaderIDs){
        glDeleteShader(shaderID);
    }
}

GLuint ShaderProgram::GetProgramID() {
    return programID;
}

std::string ShaderProgram::GetProgramName() {
    return programName;
}
