//
// Created by User on 15/11/2023.
//

#ifndef RAYTRACEVOXELENGINE_STRUCTURES_H
#define RAYTRACEVOXELENGINE_STRUCTURES_H

#include <string>

struct Voxel{
    int type;
    bool terminal;

    std::string toString(){
        return std::to_string(type);
    }
};

struct WorldSettings{

    int octreeDepth;
    int worldScale;
};

struct VoxelData{
    int voxelType; // A type in the range of 0-255
};

struct Node {
    bool terminal;
    Node *children[8];
    Voxel voxelData;

    Node(){
        terminal = false;
        voxelData = {-1};
        for(int i = 0; i < 8; i++){
            children[i] = nullptr;
        }
    }
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
