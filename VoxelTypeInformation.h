//
// Created by User on 10/12/2023.
//

#ifndef RAYTRACEVOXELENGINE_VOXELTYPEINFORMATION_H
#define RAYTRACEVOXELENGINE_VOXELTYPEINFORMATION_H

#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include "Structures.h"

class VoxelTypeInformation {
public:
    VoxelTypeInformation();
    virtual void AddVoxelType(VoxelType vt_);
    virtual std::vector<VoxelType> GetVoxelTypeInformation(int numberOfTypes);
private:
    std::vector<VoxelType> voxelTypes;
};


#endif //RAYTRACEVOXELENGINE_VOXELTYPEINFORMATION_H
