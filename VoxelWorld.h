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
#include "VoxelOctree.h"
#include "Camera.h"
#include "SRombauts/SimplexNoise.h"
#include "DeltaTime/DeltaTime.h"
#include "Structures.h"

class VoxelWorld {
private:
    SimplexNoise* simplexNoise;

    // The depth of the voxel octree
    int octreeDepth = 2;

    // The scale of the world (the largest voxel)
    int worldScale = 16;

    std::vector<Voxel> worldVoxels; // A Vector that stores all the voxels that are in the world
    int* voxelIndices; // An array that stores all voxel indexes of size chunkSize^3 * renderDist^3

    VoxelOctree* voxelOctree; // The SparseVoxelOctree for the voxels

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

    void UpdateWorldSettingsBuffer(); // Updates the world settings buffer
    void UpdateCameraBuffer(); // Updates the camera buffers
    void UpdateVoxelBuffers(); // Updates the voxel data buffers
    void RenderWorld(GLFWwindow* window, std::map<std::string, GLuint> GLHandles); // Used to run the raytracing to render the world

    void SetActiveCamera(Camera* camera_);
};


#endif //ADVANCEDVOXELENGINE_VOXELWORLD_H
