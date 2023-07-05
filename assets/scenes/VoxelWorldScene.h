//
// Created by User on 26/03/2023.
//

#ifndef ADVANCEDVOXELENGINE_VOXELWORLDSCENE_H
#define ADVANCEDVOXELENGINE_VOXELWORLDSCENE_H

#include <iostream>
#include <cmath>
#include "../../Scene.h"
#include "../../VoxelWorld.h"

class VoxelWorldScene: public Scene {
private:
    VoxelWorld* voxelWorld;
public:
    VoxelWorldScene(std::string name, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_);

    void UpdateScene(float *deltaTimePtr);
    void RenderScene(float *deltaTimePtr);
};


#endif //ADVANCEDVOXELENGINE_VOXELWORLDSCENE_H
