//
// Created by User on 10/12/2023.
//

#include "VoxelTypeInformation.h"

VoxelTypeInformation::VoxelTypeInformation(int numberOfTypes_) {

    numberOfTypes = numberOfTypes_;
}

std::vector<VoxelType> VoxelTypeInformation::GetVoxelTypeInformation() {

    std::vector<VoxelType> voxTypes;
    for(int i = 0; i < numberOfTypes; i++){

        VoxelType vt = {i, 1.0, i/(float)numberOfTypes, i/(float)numberOfTypes, i/(float)numberOfTypes, 0.0, 0.0, 0.0, 0.0};
        voxTypes.push_back(vt);
    }

    for(int i = 0; i < voxelTypes.size(); i++){

        VoxelType vt = voxelTypes.at(i);
        voxTypes.at(vt.type) = vt;
    }

    return voxTypes;
}

void VoxelTypeInformation::AddVoxelType(VoxelType vt_) {

    voxelTypes.push_back(vt_);
}
