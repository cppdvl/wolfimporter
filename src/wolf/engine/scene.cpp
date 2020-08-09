#include <memory>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <wolf/engine/scene.hpp>
#include <wolf/engine/resources/resourcemanager.hpp>

Wolf::Engine::Scene::Scene(std::string const& resourceName){

    auto spResourceManager = Wolf::Engine::ResourceManager::spGetInstance();
    auto resourceManager = *spResourceManager;

    //load the resources for the scene.
    auto spSceneResources = resourceManager[resourceName];
    auto rpSceneResources = spSceneResources.get();
    auto rpSceneResourcesJSON = reinterpret_cast<ResourceJSON*>(rpSceneResources);

    for(auto&[k,v]:rpSceneResourcesJSON->resourceData.items()){
        std::cout << k << std::endl;
    }


}

void Wolf::Engine::Scene::init(){




}
void Wolf::Engine::Scene::update(unsigned int /*msec_data*/){

}
void Wolf::Engine::Scene::render(){

}
void Wolf::Engine::Scene::finish(){
    
}