//
// Created by User on 5/07/2023.
//

#include "VoxelWorld.h"

VoxelWorld::VoxelWorld() {

    std::cout << "--- Creating Voxel World ---" << std::endl;

    // Generate buffers
    glGenBuffers(1, &voxelIndicesBuffer);
    glGenBuffers(1, &voxelDataBuffer);
    glGenBuffers(1, &activeCameraBuffer);
    glGenBuffers(1, &lightsBuffer);
    glGenBuffers(1, &worldSettingsBuffer);

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

    updateVoxels = true;
    std::cout << "Initialized Voxel World Vector in: " << DeltaTime(voxelInitStartTime) << " seconds" << std::endl;
}

VoxelWorld::~VoxelWorld() {

    delete[] voxelIndices;
}

int VoxelWorld::TotalVoxels() const {

    return pow(renderDistance, 3) * pow(chunkSize, 3);
}

int VoxelWorld::TotalWorldSize() const {

    return renderDistance * chunkSize;
}

int VoxelWorld::FlatIndex(int x_, int y_, int z_) {

    return x_ + TotalWorldSize() * (y_ + TotalWorldSize() * z_);
}

Voxel VoxelWorld::GetVoxelAt(int x_, int y_, int z_) {

    int index = voxelIndices[FlatIndex(x_, y_, z_)];
    if(index >= 0 && index < worldVoxels.size()){
        return worldVoxels.at(index);
    }

    return Voxel{};
}

// This renders the world using the ray-cast shader
void VoxelWorld::RenderWorld(GLFWwindow *window, std::map<std::string, GLuint> GLHandles) {

    // Get the screen width and height
    int win_width, win_height;
    glfwGetWindowSize(window, &win_width, &win_height);

    // Update the world settings buffer
    UpdateWorldSettingsBuffer();

    // Update the cameras buffer
    UpdateCameraBuffer();

    // Update the buffers
    UpdateVoxelBuffers();

    // Run the compute shader
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    glUseProgram(GLHandles["RaytraceProgram"]);
    glDispatchCompute(ceil(win_width / 8), ceil(win_height / 4), 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void VoxelWorld::UpdateVoxelBuffers() {

    // Make sure the voxel buffer needs to be updated before updating it
    if(updateVoxels) {

        std::cout << "Updating Voxel Buffers" << std::endl;

        // Delete the buffers before updating them to avoid memory leakage
        glDeleteBuffers(1, &voxelIndicesBuffer);
        glDeleteBuffers(1, &voxelDataBuffer);

        // Send the voxel indices to the Raytrace Shader
        glGenBuffers(1, &voxelIndicesBuffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, voxelIndicesBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, voxelIndicesBuffer);
        glBufferStorage(GL_SHADER_STORAGE_BUFFER, TotalVoxels() * sizeof(int), voxelIndices, 0);

        // Send the voxel data to the Raytrace Shader
        glGenBuffers(1, &voxelDataBuffer);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, voxelDataBuffer);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, voxelDataBuffer);
        glBufferStorage(GL_SHADER_STORAGE_BUFFER, worldVoxels.size() * sizeof(Voxel), worldVoxels.data(), 0);

        // Update updateVoxels as they have now been passed to the shader
        updateVoxels = false;
    }
}

void VoxelWorld::UpdateWorldSettingsBuffer() {

    // chunkSize, renderDistance, totalSize
    WorldSettings worldSettings = WorldSettings();
    worldSettings.renderDistance = renderDistance;
    worldSettings.chunkSize = chunkSize;
    worldSettings.totalSize = TotalWorldSize();

    // Send the world settings to the Raytrace shader
    glGenBuffers(1, &worldSettingsBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, worldSettingsBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, worldSettingsBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, sizeof(WorldSettings), &worldSettings, 0);
}

void VoxelWorld::UpdateCameraBuffer() {

    CameraStruct cameraStruct = CameraStruct();
    vec3 camPos = activeCamera->GetPosition();
    vec3 camDir = activeCamera->GetDirection();
    vec3 camRight = activeCamera->GetRight();
    vec3 camUp = activeCamera->GetUp();

    // Calculate the aspect ratio
    int win_width, win_height;
    glfwGetWindowSize(activeCamera->GetWindow(), &win_width, &win_height);
    float aspectRatio = (float)win_width/(float)win_height;

    // Set the activeCamera's data for the shader
    cameraStruct.posX = camPos.x;
    cameraStruct.posY = camPos.y;
    cameraStruct.posZ = camPos.z;
    cameraStruct.dirX = camDir.x;
    cameraStruct.dirY = camDir.y;
    cameraStruct.dirZ = camDir.z;
    cameraStruct.rightX = camRight.x;
    cameraStruct.rightY = camRight.y;
    cameraStruct.rightZ = camRight.z;
    cameraStruct.upX = camUp.x;
    cameraStruct.upY = camUp.y;
    cameraStruct.upZ = camUp.z;
    cameraStruct.aspectRatio = aspectRatio;
    cameraStruct.fov = activeCamera->GetFOV();

    // Delete the buffer before updating to avoid memory leakage
    glDeleteBuffers(1, &activeCameraBuffer);

    // Send the voxel indices to the Raytrace Shader
    glGenBuffers(1, &activeCameraBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, activeCameraBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, activeCameraBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, sizeof(CameraStruct), &cameraStruct, 0);
}

void VoxelWorld::SetActiveCamera(Camera *camera_) {

    activeCamera = camera_;
}
