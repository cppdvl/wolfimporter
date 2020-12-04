#include <memory>
#include <iostream>

#include <spdlog/spdlog.h>

#include <nlohmann/json.hpp>
#include <wolf/ecs/scene.hpp>
#include <wolf/resources/json/resourcejson.hpp>

#include <wolf/resources/resourcemanager.hpp>

Wolf::ECS::Scene::Scene(std::string const& sceneresourcename){

    auto rm = *(Wolf::Resources::ResourceManager::spGetInstance());

    //load the resources for the scene.
    auto sceneresourcejson = std::dynamic_pointer_cast<Resources::ResourceJSON>(rm[sceneresourcename]);
    assert(sceneresourcejson);

    auto [spSceneResourcesJSONTypeString, spSceneResourcesJSONType] = sceneresourcejson->getType();
    assert(spSceneResourcesJSONType == Wolf::Resources::ResourceJSON::RESOURCE_TYPE::SCENE);

    //Default Scene to render out
    spdlog::info("The following is the scene to render: ");
    sceneresourcejson->PrettyPrint();

    for(auto&[entityname, entityjson] : sceneresourcejson->items()){

        //EntityJson
        if (entityjson.is_string()) {
            auto spresourcejson = rm[entityjson.get<std::string>()];
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