//
// Created by User on 7/25/2020.
//
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <nlohmann/json.hpp>

#include <wolf/engine/ecs/component/component_name.hpp>
#include <wolf/import/resources/resourceloader_json.hpp>

using json = nlohmann::json;

Wolf::Engine::SPResource Load_RESOURCE_TYPE_SCENE(const json& RESOURCE_DATA);

struct JSON_RESOURCE_DATA_CALLBACKS {
    inline static std::map <std::string, std::function<Wolf::Engine::SPResource(const json&)>> CB{
        std::make_pair("SCENE",Load_RESOURCE_TYPE_SCENE)
    };
};


Wolf::Engine::SPResource Wolf::Import::ResourceLoaderJSON::LoadResource() {

    json j;
    std::ifstream i(mResourcePath);
    i >> j;
    try {

        auto RESOURCE_TYPE = j["RESOURCE_TYPE"];
        auto RESOURCE_DATA = j["RESOURCE_DATA"];
        auto RESOURCE_TYPE_NotFound = JSON_RESOURCE_DATA_CALLBACKS::CB.find(RESOURCE_TYPE) == JSON_RESOURCE_DATA_CALLBACKS::CB.end();
        if (RESOURCE_TYPE_NotFound) throw;
        return JSON_RESOURCE_DATA_CALLBACKS::CB[RESOURCE_TYPE](RESOURCE_DATA);
    }

    catch (std::exception&){

        std::cout << "Something went awfully bad.... set a breakpoint @: " << __FILE__ <<":"<< __LINE__ << std::endl;
        return nullptr;
    }

}

Wolf::Engine::SPResource Load_RESOURCE_TYPE_SCENE(const json& j){

    auto entities = j["entities"];
    auto vwpEntities = Wolf::Engine::ECS::VWPEntity {};
    for (auto& entity : entities){
        auto vwpComponents = Wolf::Engine::ECS::VWPComponent{};
        for (auto& key_value  : entity.items()){
            auto key = key_value.key();
            auto value = key_value.value();
            if (key == "entity_name_component"){

                Wolf::Engine::ECS::SPComponent spComponentName = std::make_shared<Wolf::Engine::ECS::ComponentName>(value);
                vwpComponents.push_back(spComponentName);

            } else if (key == "mesh_component"){

                auto rmi = Wolf::Engine::ResourceManager::spGetInstance();

                //auto& resourceName = value;
                //auto spResource = nullptr;//rmi->spGetResource(resourceName);

                /*Wolf::Engine::ECS::SPComponent spComponentMesh = std::make_shared<Wolf::Engine::ECS::Component>(spResource->getId());
                vwpComponents.push_back(spComponentMesh);*/

            }
        }

    }

    return nullptr;
}
