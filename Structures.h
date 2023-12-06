//
// Created by User on 15/11/2023.
//

#ifndef RAYTRACEVOXELENGINE_STRUCTURES_H
#define RAYTRACEVOXELENGINE_STRUCTURES_H

#include <string>

struct Voxel{
    int type = -1;
    int terminal = false; // 0 or 1 i.e. true or false
    int hasChildren = false; // 0 or 1 i.e. true or false
};

struct WorldSettings{

    int octreeDepth;
    int worldScale;
    int totalOctants;
};

struct Node {
    bool terminal;
    Node *children[8];
    Voxel voxelData;

    Node(){
        terminal = false;
        voxelData = {-1, false, false};
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

struct CS_StackEntry{
    int depth;
    int index;
    int x;
    int y;
    int z;
};

#endif //RAYTRACEVOXELENGINE_STRUCTURES_H
