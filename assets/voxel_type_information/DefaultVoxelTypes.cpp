//
// Created by User on 10/12/2023.
//

#include "DefaultVoxelTypes.h"

DefaultVoxelTypes::DefaultVoxelTypes() {

    // Create Voxel Type for 0
    VoxelType _1 = {1, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0};
    AddVoxelType(_1);
}
