//
// Created by User on 15/11/2023.
//

#ifndef RAYTRACEVOXELENGINE_STRUCTURES_H
#define RAYTRACEVOXELENGINE_STRUCTURES_H

#include <string>

struct iVec3{
    int x, y, z;

    iVec3(int x_, int y_, int z_){
        x = x_;
        y = y_;
        z = z_;
    }
};

struct fVec3{
    float x, y, z;

    fVec3(float x_, float y_, float z_){
        x = x_;
        y = y_;
        z = z_;
    }
};

struct Voxel{
    int type;

    std::string toString(){
        return std::to_string(type);
    }
};

struct VoxelType{
    int type;
    float opacity;
    float r;
    float g;
    float b;
    float emission_r;
    float emission_g;
    float emission_b;
    float emission_strength;
};

struct Light{
    float size;
    float x, y, z;
    float dirX, dirY, dirZ;
    float r, g, b;
    float intensity;
    int type; // 0 = ambient, 1 = directional, 2 = point, 3 = spot

    Light(int type_, float size_, fVec3 position_, fVec3 direction_, fVec3 colour_, float intensity_){

        type = type_;
        size = size_;

        x = position_.x;
        y = position_.y;
        z = position_.z;

        dirX = direction_.x;
        dirY = direction_.y;
        dirZ = direction_.z;

        r = colour_.x;
        g = colour_.y;
        b = colour_.z;

        intensity = intensity_;
    }
};

struct WorldSettings{

    int numberOfLights;
    int renderDistance;
    int chunkSize;
    int totalSize;
};

struct LightingSettings{
    int state; // Passing in a random state allows for better random generation each frame
    int maxBounces;
};

#endif //RAYTRACEVOXELENGINE_STRUCTURES_H
