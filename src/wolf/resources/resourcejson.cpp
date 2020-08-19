//
// Created by User on 8/19/2020.
//
#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <wolf/resources/resourcejson.hpp>


Wolf::Resources::ResourceJSON::ResourceJSON(const std::string& url) : Resource() {

    auto assertionHandling = [](auto& ok, auto& msg, auto param){
        if (ok) return;
        _assert(msg, __FILE__, __LINE__);
        std::cout << msg << " : " << param << std::endl;
        assert(0);
    };

    std::ifstream ifs(url);
    assertionHandling(ifs, "Error opening json resource: ", url);
    nlohmann::json jsn;
    ifs >> jsn;
    ifs.close();

    auto resourceTypeFieldFound = jsn.find("RESOURCE_TYPE") != jsn.end();
    assertionHandling(resourceTypeFieldFound, "RESOURCE_TYPE entry wasn't there.", std::string{});
    auto resourceTypeString = jsn["RESOURCE_TYPE"];
    resourceType = Wolf::Resources::ResourceJSON::mapStringType[resourceTypeString];

    auto resourceDataFieldFound = jsn.find("RESOURCE_DATA") != jsn.end();
    assertionHandling(resourceDataFieldFound, "RESOURCE_DATA entry wasn't there.", std::string{});
    resourceData = jsn["RESOURCE_DATA"];

}