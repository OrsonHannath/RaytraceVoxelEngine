//
// Created by User on 26/03/2023.
//

#include "Scene.h"

// Define vertices and indices variables
GLfloat vertices[] = {-1.0f, -1.0f , 0.0f, 0.0f, 0.0f,
                      -1.0f,  1.0f , 0.0f, 0.0f, 1.0f,
                      1.0f,  1.0f , 0.0f, 1.0f, 1.0f,
                      1.0f, -1.0f , 0.0f, 1.0f, 0.0f};

GLuint indices[] = {0, 2, 1,
                    0, 3, 2};

Scene::Scene(std::string name_, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_) {

    name = name_;
    window = window_;
    GLHandles = GLHandles_;

    glfwGetWindowSize(window, &win_width, &win_height);

    glCreateVertexArrays(1, &VAO);
    glCreateBuffers(1, &VBO);
    glCreateBuffers(1, &EBO);

    glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glNamedBufferData(EBO, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexArrayAttrib(VAO, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

    glEnableVertexArrayAttrib(VAO, 1);
    glVertexArrayAttribBinding(VAO, 1, 0);
    glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));

    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 5 * sizeof(GLfloat));
    glVertexArrayElementBuffer(VAO, EBO);

    glCreateTextures(GL_TEXTURE_2D, 1, &screenTex);
    glTextureParameteri(screenTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(screenTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(screenTex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(screenTex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureStorage2D(screenTex, 1, GL_RGBA32F, win_width, win_height);
    glBindImageTexture(0, screenTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
}

void Scene::SetGLHandle(std::string handleStr_, GLuint handleVal_) {

    GLHandles[handleStr_] = handleVal_;
}

std::string Scene::GetName(){

    return name;
}

void Scene::UpdateScene(float* deltaTimePtr){

};

void Scene::RenderScene(float* deltaTimePtr) {

    // Use the main program to render the scene
    glUseProgram(GLHandles["MainProgram"]);
    glBindTextureUnit(0, screenTex);
    glUniform1i(glGetUniformLocation(GLHandles["MainProgram"], "screen"), 0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

    // Not sure what the use of these are (causes bad flashing when they're not commented out)
    //glfwSwapBuffers(window);
    //glfwPollEvents();
}