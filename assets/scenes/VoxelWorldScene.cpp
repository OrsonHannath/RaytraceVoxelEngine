//
// Created by User on 26/03/2023.
//

#include "VoxelWorldScene.h"

VoxelWorldScene::VoxelWorldScene(std::string name, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_) : Scene(name, window_, GLHandles_) {

    // Create the Voxel World
    voxelWorld = new VoxelWorld();
}

void VoxelWorldScene::UpdateScene(float *deltaTimePtr) {

}

void VoxelWorldScene::RenderScene(float *deltaTimePtr) {

    // Compute the voxels
    voxelWorld->RenderWorld(window, GLHandles);

    // Render the scene
    Scene::RenderScene(deltaTimePtr);
}
