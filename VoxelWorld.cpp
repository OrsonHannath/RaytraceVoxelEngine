//
// Created by User on 5/07/2023.
//

#include "VoxelWorld.h"

VoxelWorld::VoxelWorld() {

    std::cout << "--- Creating Voxel World ---" << std::endl;

    // Generate buffers
    glGenBuffers(1, &voxelIndicesBuffer);
    glGenBuffers(1, &voxelDataBuffer);

    // Create the Simplex Perlin Noise Object
    simplexNoise = new SimplexNoise(0.1, 1.0, 2.0, 0.5);

    // Set the Voxel Indices Array
    voxelIndices = new int[TotalVoxels()]{-1};
    std::cout << "Initialized Voxel Indices Array" << std::endl;

    // Instantiate the Voxel World using the SimplexNoise
    double voxelInitStartTime = CurrentTime();
    for(int x = 0; x < TotalWorldSize(); x++){
        for(int y = 0; y < TotalWorldSize(); y++){
            for(int z = 0; z < TotalWorldSize(); z++){

                // Determine the voxels type using the simplex noise
                int voxelType = (int)roundf(simplexNoise->fractal(1, x, y, z) * 255);

                // Create the voxel structure and add it to the voxels vector
                Voxel voxel = {voxelType};
                worldVoxels.push_back(voxel);

                int voxelIndex = (int)worldVoxels.size() - 1;
                voxelIndices[FlatIndex(x, y, z)] = voxelIndex;
            }
        }
    }
    std::cout << "Initialized Voxel World Vector in: " << DeltaTime(voxelInitStartTime) << " seconds" << std::endl;
}

VoxelWorld::~VoxelWorld() {

    delete[] voxelIndices;
}

void VoxelWorld::UpdateVoxelIndices() {

}

void VoxelWorld::SetRenderDistance(int renderDist_) {

}

int VoxelWorld::TotalVoxels() const {

    return pow(chunkSize, 3) * pow(renderDist, 3);
}

int VoxelWorld::TotalWorldSize() const {

    return chunkSize * renderDist;
}

int VoxelWorld::FlatIndex(int x_, int y_, int z_) {

    return (z_ * TotalWorldSize() * TotalWorldSize()) + (y_ * TotalWorldSize()) + x_;
}

Voxel VoxelWorld::GetVoxelAt(int x_, int y_, int z_) {

    return worldVoxels.at(voxelIndices[FlatIndex(x_, y_, z_)]);
}

// This renders the world using the ray-cast shader
void VoxelWorld::RenderWorld(GLFWwindow *window, std::map<std::string, GLuint> GLHandles) {

    // Get the screen width and height
    int win_width, win_height;
    glfwGetWindowSize(window, &win_width, &win_height);

    // Update the buffers
    UpdateVoxelBuffers();

    // Run the compute shader
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    glUseProgram(GLHandles["RaytraceProgram"]);
    glDispatchCompute(ceil(win_width / 8), ceil(win_height / 4), 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void VoxelWorld::UpdateVoxelBuffers() {

    // Send the voxel indices to the Raytrace Shader
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, voxelIndicesBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, voxelIndicesBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, TotalVoxels(), voxelIndices, 0);

    // Send the voxel data to the Raytrace Shader
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, voxelDataBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, voxelDataBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, worldVoxels.size() * sizeof(Voxel), worldVoxels.data(), 0);
}
