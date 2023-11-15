//
// Created by User on 10/11/2023.
//

#include "SparseVoxelOctree.h"

SparseVoxelOctree::SparseVoxelOctree(int size_, int maxDepth_) {

    size = size_;
    maxDepth = maxDepth_;
    root = nullptr;
}

void SparseVoxelOctree::Insert(fVec3 point_, VoxelData data_) {

    InsertImpl(&root, point_, data_, iVec3(0,0,0), 0);
}

void SparseVoxelOctree::InsertImpl(Node **node_, fVec3 point_, VoxelData data_, iVec3 position_, int depth_) {

    if(*node_ == nullptr){
        *node_ = new Node;
    }

    //(*node_)->data = data_;
    if(depth_ == maxDepth){

        (*node_)->terminal = true;
        return;
    }

    float size_ = size / std::exp2(depth_);
    iVec3 childPos(
            point_.x >= (size_ * (float)position_.x) + (size_ / 2.0f),
            point_.y >= (size_ * (float)position_.y) + (size_ / 2.0f),
            point_.z >= (size_ * (float)position_.z) + (size_ / 2.0f)
    );

    int childIndex = (childPos.x << 0) | (childPos.y << 1) | (childPos.z << 2);

    position_ = {
            (position_.x << 1) | childPos.x,
            (position_.y << 1) | childPos.y,
            (position_.z << 1) | childPos.z
    };

    InsertImpl(&(*node_)->children[childIndex], point_, data_, position_, ++depth_);
}