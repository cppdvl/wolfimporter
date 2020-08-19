#include <memory>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <wolf/ecs/scene.hpp>
#include <wolf/resources/resourcejson.hpp>
#include <wolf/resources/resourcemanager.hpp>
Wolf::ECS::Scene::Scene(std::string const& resourceName){

    auto spResourceManager = Wolf::Resources::ResourceManager::spGetInstance();
    auto resourceManager = *spResourceManager;

    //load the resources for the scene.
    auto spSceneResources = resourceManager[resourceName];
    auto rpSceneResources = spSceneResources.get();
    auto rpSceneResourcesJSON = reinterpret_cast<Wolf::Resources::ResourceJSON*>(rpSceneResources);
    auto [rpSceneResourcesJSONTypeString, rpSceneResourcesJSONType] = rpSceneResourcesJSON->getType();
    std::cout << "rpSceneResourcesJSON is a: " << rpSceneResourcesJSONTypeString << std::endl;

    auto bCond = rpSceneResourcesJSONType == Wolf::Resources::ResourceJSON::RESOURCE_TYPE::SCENE;
    if (!bCond){
        std::cout << "The fetched JSON [" << resourceName << "] is not a scene!!!" << std::endl;
        _assert("Fetched Json not a scene", __FILE__, __LINE__);
        assert(bCond);
    }
    for(auto&[k,e]:rpSceneResourcesJSON->resourceData.items()){
        std::cout << k << std::endl;
        auto name = k;

    }


}

void Wolf::ECS::Scene::init(){




}
void Wolf::ECS::Scene::update(unsigned int /*msec_data*/){

}
void Wolf::ECS::Scene::render(){

}
void Wolf::ECS::Scene::finish(){
    
}