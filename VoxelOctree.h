//
// Created by User on 15/11/2023.
//

#ifndef RAYTRACEVOXELENGINE_VOXELOCTREE_H
#define RAYTRACEVOXELENGINE_VOXELOCTREE_H

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "Structures.h"

class VoxelOctree {
public:
    VoxelOctree(int size, int maxDepth);
    void Insert(fVec3 point, Voxel voxData_);
    void FlattenOctree(std::vector<Voxel>& voxelsVector);
    void GetChildNodes(std::vector<Voxel>& flattenedNodes, int parentIndex, int targetDepth, std::vector<Voxel>& childNodes, std::vector<int>& indices);

private:
    void Insert(Node **node, fVec3 point, Voxel voxData_, iVec3 position, int depth);
    void FlattenOctree(Node* node, std::vector<Voxel>& voxelsVector);

private:
    Node *m_Root;
    int m_Size;
    int m_MaxDepth;
};


#endif //RAYTRACEVOXELENGINE_VOXELOCTREE_H
