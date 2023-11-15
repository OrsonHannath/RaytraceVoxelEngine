cmake_minimum_required(VERSION 3.21)
project(RaytraceVoxelEngine)

set(CMAKE_CXX_STANDARD 14)

# Add my custom libraries to the include and link directories
set(CUSTOM_LIBRARIES_DIR libraries/Custom)
include_directories(${CUSTOM_LIBRARIES_DIR})

# Add my libraries to the include and link directories
set(LIBRARIES_DIR libraries)
include_directories(${LIBRARIES_DIR})

# Add my assets to the include and link directories
set(ASSETS_INCLUDE_DIR assets)
include_directories(${ASSETS_INCLUDE_DIR})

# Add my scene assets to the include and link directories
set(SCENE_INCLUDE_DIR assets/scenes)
include_directories(${SCENE_INCLUDE_DIR})

# Add my scene assets to the include and link directories
set(SHADER_PROGRAM_HANDLER_INCLUDE_DIR assets/shader_program_handlers)
include_directories(${SHADER_PROGRAM_HANDLER_INCLUDE_DIR})

# Setup the locations that the GLEW libraries can be found on disk
set(GLEW_INCLUDE_DIR C:/libs/GLEW/include/GL) # set(VAR_NAME path)
set(GLEW_LIB_DIR C:/libs/GLEW/lib/Release/x64) # set(VAR_NAME path)

# Setup the locations that GLFW libraries can be found
set(GLFW_INCLUDE_DIR C:/libs/GLFW/include/GLFW) # set(VAR_NAME path)
set(GLFW_LIB_DIR C:/libs/GLFW/lib-mingw-w64) # set(VAR_NAME path)

# Setup the locations that GLFW libraries can be found
set(GLM_INCLUDE_DIR C:/libs/GLM) # set(VAR_NAME path)

set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(${GLEW_INCLUDE_DIR}) # include_directories(${VAR_NAME}) *used for include files*
include_directories(${GLFW_INCLUDE_DIR}) # include_directories(${VAR_NAME}) *used for include files*
include_directories(${GLM_INCLUDE_DIR}) # include_directories(${VAR_NAME}) *used for include files*

link_directories(${GLEW_LIB_DIR}) # link_directories(${VAR_NAME}) *used for dll/binary/lib files*
link_directories(${GLFW_LIB_DIR}) # link_directories(${VAR_NAME}) *used for dll/binary/lib files*

add_executable(RaytraceVoxelEngine main.cpp OpenGLApp.h OpenGLApp.cpp Scene.h Scene.cpp SceneManager.h SceneManager.cpp ShaderProgram.h ShaderProgram.cpp ShaderProgramHandler.h ShaderProgramHandler.cpp assets/scenes/VoxelWorldScene.h assets/scenes/VoxelWorldScene.cpp libraries/Custom/DeltaTime/DeltaTime.h libraries/Custom/DeltaTime/DeltaTime.cpp assets/shader_program_handlers/TestingShaderProgramHandler.h assets/shader_program_handlers/TestingShaderProgramHandler.cpp libraries/Custom/Vector3/Vector3.h VoxelWorld.cpp VoxelWorld.h libraries/SRombauts/SimplexNoise.cpp libraries/SRombauts/SimplexNoise.h Camera.cpp Camera.h Structures.h VoxelOctree.cpp VoxelOctree.h)

target_link_libraries(${PROJECT_NAME} glfw3 glew32 opengl32 -static-libgcc -static-libstdc++) # Link the libraries to the project
