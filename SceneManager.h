//
// Created by User on 26/03/2023.
//

#ifndef ADVANCEDVOXELENGINE_SCENEMANAGER_H
#define ADVANCEDVOXELENGINE_SCENEMANAGER_H

#include <map>
#include <iostream>
#include "Scene.h"

class SceneManager {
private:
    Scene* currentScene;
    std::map<std::string, Scene*> sceneMap;
    float* deltaTimePtr;
public:

    SceneManager(float* deltaTime_);

    void RenderScene(Scene* scene_);
    void AddScene(Scene* scene_);
    void SetCurrentScene(Scene* scene_);
    void UpdateCurrentScene(float* deltaTime);
    void RenderCurrentScene(float* deltaTime);

    Scene* GetScene(std::string name);
    Scene* GetCurrentScene();
};


#endif //ADVANCEDVOXELENGINE_SCENEMANAGER_H
