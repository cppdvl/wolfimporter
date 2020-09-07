//
// Created by User on 8/19/2020.
//
#include <string>
#include <fstream>
#include <iostream>
#include <wolf/resources/json/resourcejson.hpp>
#include <nlohmann/json.hpp>

Wolf::Resources::ResourceJSON::ResourceJSON(const nlohmann::json& j, const std::string& resourceTypeString) :
Resource(),
nlohmann::json(j),
mResourceType(Wolf::Resources::ResourceJSON::mapStringType[resourceTypeString]){

}

nlohmann::json _checkJsnPath(const std::filesystem::path& pth){

    auto assertionHandling = [](auto& ok, auto& msg, auto param){
        if (ok) return;
        _assert(msg, __FILE__, __LINE__);
        std::cout << msg << " : " << param << std::endl;
        assert(0);

    };

    std::ifstream ifs(pth);
    assertionHandling(ifs, "Error opening json resource: ", pth);
    nlohmann::json jsn;
    ifs >> jsn;
    ifs.close();

    return jsn;

}

static nlohmann::json _checkJsn(const nlohmann::json&jsn){

    auto assertionHandling = [](auto& ok, auto& msg, auto param){
        if (ok) return;
        _assert(msg, __FILE__, __LINE__);
        std::cout << msg << " : " << param << std::endl;
        assert(0);
    };
    auto resourceTypeFieldFound = jsn.find("RESOURCE_TYPE") != jsn.end();
    assertionHandling(resourceTypeFieldFound, "RESOURCE_TYPE entry wasn't there.", std::string{});
    auto resourceDataFieldFound = jsn.find("RESOURCE_DATA") != jsn.end();
    assertionHandling(resourceDataFieldFound, "RESOURCE_DATA entry wasn't there.", std::string{});
    return jsn;
}

static Wolf::Resources::SPResource _generateResourceJSON(const nlohmann::json&jsn){

    auto resourceTypeString = jsn["RESOURCE_TYPE"];
    auto resourceJsonData = jsn["RESOURCE_DATA"];
    return std::make_shared<Wolf::Resources::ResourceJSON>(resourceJsonData, resourceTypeString);

}

Wolf::Resources::SPResource Wolf::Resources::ResourceJSON::CreateResourceJSon(const std::filesystem::path& pth){
   return _generateResourceJSON(_checkJsn(_checkJsnPath(pth)));
}

Wolf::Resources::SPResource Wolf::Resources::ResourceJSON::CreateResourceJSon(const std::string& jsnstring) {
    return _generateResourceJSON(_checkJsn(nlohmann::json(jsnstring)));
}