//
// Created by User on 26/03/2023.
//

#include "VoxelWorldScene.h"

VoxelWorldScene::VoxelWorldScene(std::string name, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_) : Scene(name, window_, GLHandles_) {

    // Create the Camera
    mainCamera = new Camera(glm::vec3(0, 0, 10), 25, 0.5, window_);

    // Create the Voxel World
    voxelWorld = new VoxelWorld();
    voxelWorld->SetActiveCamera(mainCamera);
    voxelWorld->SetRaytraceProgram(GLHandles_.at("RaytraceProgram"));

    // Create a global light
    Light ambientLight = Light(1, vec3(0, 0, 0), vec3(236.0/255.0, 225.0/255.0, 188.0/255.0), 0.25, true, true);
    voxelWorld->AddLight(ambientLight);
}

void VoxelWorldScene::UpdateScene(float *deltaTimePtr) {

}

void VoxelWorldScene::RenderScene(float *deltaTimePtr) {

    // Update the Main Camera
    mainCamera->UpdateCamera(deltaTimePtr);

    // Compute the voxels
    voxelWorld->RenderWorld(window, GLHandles);

    // Render the scene
    Scene::RenderScene(deltaTimePtr);
}
