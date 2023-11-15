//
// Created by User on 15/11/2023.
//

#include "VoxelOctree.h"

VoxelOctree::VoxelOctree(int size_, int maxDepth_) {

    m_Size = size_;
    m_MaxDepth = maxDepth_;
    m_Root = nullptr;
}

// https://www.youtube.com/watch?v=NjCp-HIZTcA&ab_channel=Ozown
void VoxelOctree::Insert(fVec3 point, Voxel voxData_) {

    Insert(&m_Root, point, voxData_, iVec3(0,0,0), 0);
}

// https://www.youtube.com/watch?v=NjCp-HIZTcA&ab_channel=Ozown
void VoxelOctree::Insert(Node **node, fVec3 point, Voxel voxData_, iVec3 position, int depth) {

    // We only create nodes that have values, hence the sparse name
    if (*node == nullptr) {
        *node = new Node;
    }

    if (depth == m_MaxDepth) {
        (*node)->terminal = true;
        (*node)->voxelData = voxData_;
        return;
    }

    /*
        We get the size of the current voxel, which we use to find the
        lower boundary of the volume by multiplying it with all the previous positions.
        Once that is aquired we take the point we are
        intersted in and minus it by that boundary, which is then divided by the size
        of the current voxel. This gives us a number between 0-1 which we round to find out
        which child this point belongs to.
    */

    //(*node)->voxelData = voxData_;
    float size = (1.0f / std::exp2(depth)) * m_Size;
    iVec3 childPos = {
            (int)std::round((point.x - ((float)position.x * size)) / size),
            (int)std::round((point.y - ((float)position.y * size)) / size),
            (int)std::round((point.z - ((float)position.z * size)) / size),
    };
    // We get the child index by or-ing together all the axis
    int childIndex = (childPos.x << 0) | (childPos.y << 1) | (childPos.z << 2);

    // To keep track of where we are in the tree we keep track of all the choices we have made so far.
    position = {
            (position.x << 1) | childPos.x,
            (position.y << 1) | childPos.y,
            (position.z << 1) | childPos.z,
    };

    // This continues until we are at our max resolution
    Insert(&(*node)->children[childIndex], point, voxData_, position, ++depth);
}

// Calling this function will trigger a recursive call to flatten the voxel octree
void VoxelOctree::FlattenOctree(std::vector<Voxel> &voxelsVector) {

    // As long as root is not a nullptr begin the recursive call from the root node
    if(m_Root != nullptr){
        FlattenOctree(m_Root, voxelsVector);
    }
}

void VoxelOctree::FlattenOctree(Node *node, std::vector<Voxel> &voxelsVector) {

    // Ensure that the node is not a nullptr
    if(node == nullptr){
        return;
    }

    // Store the node into the array
    voxelsVector.push_back(node->voxelData);

    // Recursively flatten the children
    for(int i = 0; i < 8; i++){

        FlattenOctree(node->children[i], voxelsVector);
    }
}