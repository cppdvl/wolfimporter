//
// Created by User on 7/25/2020.
//
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <nlohmann/json.hpp>

#include <wolf/ecs/component/component_name.hpp>
#include <wolf/import/resources/resourceloader_json.hpp>

using json = nlohmann::json;

Wolf::Resources::SPResource Load_RESOURCE_TYPE_SCENE(const json& RESOURCE_DATA);

struct JSON_RESOURCE_DATA_CALLBACKS {
    inline static std::map <std::string, std::function<Wolf::Resources::SPResource(const json&)>> CB{
        std::make_pair("SCENE",Load_RESOURCE_TYPE_SCENE)
    };
};


Wolf::Resources::SPResource Wolf::Import::ResourceLoaderJSON::LoadResource() {

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

