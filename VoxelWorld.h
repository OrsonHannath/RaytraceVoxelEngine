//
// Created by User on 5/07/2023.
//

#ifndef ADVANCEDVOXELENGINE_VOXELWORLD_H
#define ADVANCEDVOXELENGINE_VOXELWORLD_H

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <cstring>
#include "Camera.h"
#include "SRombauts/SimplexNoise.h"
#include "DeltaTime/DeltaTime.h"
#include "Structures.h"

class VoxelWorld {
private:
    SimplexNoise* simplexNoise;

    // The number of chunks viewed in the world;
    int renderDistance = 4;

    // The number of voxels along x, y, z axis
    int chunkSize = 32;

    // Used to determine whether the world voxels have been updated and therefor need to be updated on raytracing shader
    bool updateVoxels = true;

    // A Vector that stores all the voxels that are in the world
    std::vector<Voxel> worldVoxels;

    // An array that stores all voxel indexes of size chunkSize^3 * renderDist^3
    int* voxelIndices;

    // A vector that stores all the lights in the scene
    std::vector<Light> sceneLights;

    // Identifier for the Raytrace Shader Program
    GLuint raytraceProgram;

    // Identifiers for all shader buffers
    GLuint voxelDataBuffer;
    GLuint voxelIndicesBuffer;
    GLuint activeCameraBuffer;
    GLuint lightsBuffer;
    GLuint worldSettingsBuffer;

    Camera* activeCamera;
public:
    VoxelWorld();
    ~VoxelWorld();

    Voxel GetVoxelAt(int x_, int y_, int z_); // Returns the voxel from the voxel vector based on the flat index in voxel indices
    int TotalVoxels() const; // Returns the total number of voxels in the rendered world
    int TotalWorldSize() const; // Returns the total size of the world i.e. chunkSize * renderDist
    int FlatIndex(int x_, int y_, int z_); // Returns a flattened index from a 3D position

    void UpdateVoxel(int voxelIndex, Voxel replacementVoxel); // Updates a single voxel in the voxels SBO
    void UpdateLight(int lightIndex, Voxel replacementLight); // Updates a single light in the lights SBO
    void UpdateWorldSettingsBuffer(); // Updates the world settings buffer
    void UpdateCameraBuffer(); // Updates the camera buffers
    void UpdateVoxelBuffers(); // Updates the voxel data buffers
    void UpdateLightsBuffer(); // Updates all lights in the lights buffer
    void RenderWorld(GLFWwindow* window, std::map<std::string, GLuint> GLHandles); // Used to run the raytracing to render the world

    void SetActiveCamera(Camera* camera_);
    void SetRaytraceProgram(GLuint programID);

    void AddLight(Light light);
};


#endif //ADVANCEDVOXELENGINE_VOXELWORLD_H
