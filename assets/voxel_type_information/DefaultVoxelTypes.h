//
// Created by User on 10/12/2023.
//

#ifndef RAYTRACEVOXELENGINE_DEFAULTVOXELTYPES_H
#define RAYTRACEVOXELENGINE_DEFAULTVOXELTYPES_H

#include "../../VoxelTypeInformation.h"

class DefaultVoxelTypes : public VoxelTypeInformation {
public:
    DefaultVoxelTypes(int numberOfTypes);
    void CompileVoxelTypes();
};


#endif //RAYTRACEVOXELENGINE_DEFAULTVOXELTYPES_H
