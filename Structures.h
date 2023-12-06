//
// Created by User on 15/11/2023.
//

#ifndef RAYTRACEVOXELENGINE_STRUCTURES_H
#define RAYTRACEVOXELENGINE_STRUCTURES_H

#include <string>

struct Voxel{
    int type;

    std::string toString(){
        return std::to_string(type);
    }
};

struct Light{
    float size;
    float x;
    float y;
    float z;
    float r;
    float g;
    float b;
    float intensity;
    int global; // Really just a bool but needs to be int to deal with padding when passed to shader
    int ambient; // Really just a bool but needs to be int to deal with padding when passed to shader

    Light(float size_, vec3 position_, vec3 colour_, float intensity_, bool global_, bool ambient_){

        size = size_;

        x = position_.x;
        y = position_.y;
        z = position_.z;

        r = colour_.x;
        g = colour_.y;
        b = colour_.z;

        intensity = intensity_;

        global = global_;
        ambient = ambient_;
    }
};

struct WorldSettings{

    int numberOfLights;
    int renderDistance;
    int chunkSize;
    int totalSize;
};

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

#endif //RAYTRACEVOXELENGINE_STRUCTURES_H
