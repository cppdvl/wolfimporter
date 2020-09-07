#include <memory>
#include <iostream>

#include <spdlog/spdlog.h>

#include <nlohmann/json.hpp>
#include <wolf/ecs/scene.hpp>
#include <wolf/resources/json/resourcejson.hpp>

#include <wolf/resources/resourcemanager.hpp>

Wolf::ECS::Scene::Scene(std::string const& resourceName){

    auto resourceManager = *(Wolf::Resources::ResourceManager::spGetInstance());

    //load the resources for the scene.
    auto spSceneResourcesJSON = std::dynamic_pointer_cast<Resources::ResourceJSON>(resourceManager[resourceName]) ;
    auto [spSceneResourcesJSONTypeString, spSceneResourcesJSONType] = spSceneResourcesJSON->getType();
    spdlog::info("spSceneResourcesJSON is a: {:s}", spSceneResourcesJSONTypeString);

    assert(spSceneResourcesJSONType == Wolf::Resources::ResourceJSON::RESOURCE_TYPE::SCENE);

    for(auto&[entityName, entityJSon] : spSceneResourcesJSON->items()){

        //TODO: We need name resolution in the resource manager, but seemlessly. WolfCamera//0 should be loaded with not knowing it's not yet mounted.
        if (entityJSon.is_string() == false) std::cout << std::setw(4) << entityJSon << std::endl;
        else {
            auto spResourceJSON = resourceManager[entityJSon.get<std::string>()];
        }

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