//
// Created by User on 8/19/2020.
//
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include <wolf/resources/json/resourcejson.hpp>
#include <nlohmann/json.hpp>

Wolf::Resources::ResourceJSON::ResourceJSON(const nlohmann::json& j, const std::string& resourceTypeString) :
Resource(),
nlohmann::json(j),
mResourceType(resourceTypeString.empty() ? Wolf::Resources::ResourceJSON::RESOURCE_TYPE::JSONOBJECT : Wolf::Resources::ResourceJSON::mapStringType[resourceTypeString]){

}

nlohmann::json _checkJsnPath(const std::filesystem::path& pth){

    std::ifstream ifs(pth);
    assert(ifs.is_open());
    nlohmann::json jsn;
    ifs >> jsn;
    ifs.close();
    return jsn;
}



static Wolf::Resources::SPResource _generateResourceJSON(const nlohmann::json&jsn){

    assert(jsn.find("RESOURCE_TYPE")!=jsn.end()  && jsn.find("RESOURCE_DATA")!=jsn.end());

    auto resourceTypeString = jsn["RESOURCE_TYPE"];
    auto resourceJsonData = jsn["RESOURCE_DATA"];
    return std::make_shared<Wolf::Resources::ResourceJSON>(resourceJsonData, resourceTypeString);

}

Wolf::Resources::SPResource Wolf::Resources::ResourceJSON::CreateResourceJSON(const std::filesystem::path&pth){

    auto sp = _generateResourceJSON(_checkJsnPath(pth));
    //spjson.PrettyPrint();
    return sp;
}

Wolf::Resources::SPResource Wolf::Resources::ResourceJSON::CreateResourceJSON(const std::string&jsnstring) {
    auto sp = _generateResourceJSON(nlohmann::json(jsnstring));
    return sp;
}

Wolf::Resources::SPResource Wolf::Resources::ResourceJSON::CreateResourceJSON(const nlohmann::json & j) {

    auto jsonwrapper = nlohmann::json{};
    jsonwrapper["RESOURCE_TYPE"] = mapTypeString[RESOURCE_TYPE::JSONOBJECT];
    jsonwrapper["RESOURCE_DATA"] = j;
    return _generateResourceJSON(jsonwrapper);

}