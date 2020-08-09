//
// Created by User on 7/26/2020.
//
#include <fstream>
#include <iostream>
#include <algorithm>
#include <wolf/engine/resources/resource.hpp>
#include <wolf/engine/resources/resourcemanager.hpp>

Wolf::Engine::SPResource Wolf::Engine::ResourceFactory::CreateResource(std::string const& url){

    std::string extension;
    auto pos = url.find_last_of(".") + 1;
    if (pos != std::string::npos){
        extension = url.substr(pos);
        std::for_each(extension.begin(), extension.end(), [&](auto& c){
            c = std::tolower(c);
        });

    }
    if (extension == "json"){

        auto spResource = std::make_shared<Wolf::Engine::ResourceJSON>(url);
        return std::static_pointer_cast<Wolf::Engine::Resource>(spResource);

    } /*else if (extension == " "){

    }*/
    return nullptr;
}

Wolf::Engine::ResourceJSON::ResourceJSON(const std::string& url) : Resource() {

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
    resourceType = Wolf::Engine::ResourceJSON::mapStringType[resourceTypeString];

    auto resourceDataFieldFound = jsn.find("RESOURCE_DATA") != jsn.end();
    assertionHandling(resourceDataFieldFound, "RESOURCE_DATA entry wasn't there.", std::string{});
    resourceData = jsn["RESOURCE_DATA"];

}

