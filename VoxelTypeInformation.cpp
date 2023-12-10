//
// Created by User on 10/12/2023.
//

#include "VoxelTypeInformation.h"

VoxelTypeInformation::VoxelTypeInformation() {


}

std::vector<VoxelType> VoxelTypeInformation::GetVoxelTypeInformation(int numberOfTypes) {

    std::vector<VoxelType> voxTypes;
    for(int i = 0; i < numberOfTypes; i++){

        VoxelType vt = {i, 1.0, i/(float)numberOfTypes, i/(float)numberOfTypes, i/(float)numberOfTypes, 0.0, 0.0, 0.0, 0.0};
        voxTypes.push_back(vt);
    }

    for(int i = 0; i < voxelTypes.size(); i++){

        VoxelType vt = voxTypes.at(i);
        voxTypes.at(vt.type) = vt;
    }

    return voxTypes;
}

void VoxelTypeInformation::AddVoxelType(VoxelType vt_) {


}
