//
// Created by User on 10/12/2023.
//

#include "DefaultVoxelTypes.h"

DefaultVoxelTypes::DefaultVoxelTypes(int numberOfTypes) : VoxelTypeInformation(numberOfTypes) {

    CompileVoxelTypes();
}

void DefaultVoxelTypes::CompileVoxelTypes() {

    // Create Voxel Types
    AddVoxelType({1, 1.0, 0.235, 0.231, 0.345, 0.0, 0.0, 0.0, 0.01});
    AddVoxelType({2, 1.0, 0.000, 0.333, 0.352, 0.0, 0.0, 0.0, 0.01});
    AddVoxelType({3, 1.0, 0.137, 0.380, 0.356, 0.0, 0.0, 0.0, 0.01});
    AddVoxelType({4, 1.0, 0.000, 0.501, 0.443, 0.0, 0.0, 0.0, 0.01});
    AddVoxelType({5, 1.0, 0.152, 0.682, 0.474, 0.0, 0.0, 0.0, 0.01});
    AddVoxelType({6, 1.0, 0.000, 0.776, 0.631, 0.0, 0.0, 0.0, 0.01});
    AddVoxelType({7, 1.0, 0.725, 0.725, 0.725, 0.0, 0.0, 0.0, 0.01});
    AddVoxelType({8, 1.0, 0.800, 0.772, 0.780, 0.0, 0.0, 0.0, 0.01});
    AddVoxelType({9, 1.0, 0.870, 0.901, 0.890, 0.0, 0.0, 0.0, 0.01});

    // If the highest type number set is bigger than the number of types then update numberOfTypes
    for(int i = 0; i < voxelTypes.size(); i++){

        if(numberOfTypes <= voxelTypes.at(i).type){
            numberOfTypes = voxelTypes.at(i).type + 1;
        }
    }
}
