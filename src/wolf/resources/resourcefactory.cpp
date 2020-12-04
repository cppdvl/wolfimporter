//
// Created by User on 8/19/2020.
//

#include <wolf/resources/json/resourcejson.hpp>
#include <wolf/resources/resourcefactory.hpp>


Wolf::Resources::SPResource Wolf::Resources::ResourceFactory::CreateResource(std::string const& url){

    std::string extension;
    auto pos = url.find_last_of(".") + 1;
    if (pos != std::string::npos){
        extension = url.substr(pos);
        std::for_each(extension.begin(), extension.end(), [&](auto& c){
            c = std::tolower(c);
        });

    }
    if (extension == "json"){

        auto spResource = Wolf::Resources::ResourceJSON::CreateResourceJSON(std::filesystem::path(url));
        return spResource;

    } /*else if (extension == " "){

    }*/
    return nullptr;
}

Wolf::Resources::SPResource Wolf::Resources::ResourceFactory::CreateResource(const nlohmann::json &j)
{
    auto spresource = Wolf::Resources::ResourceJSON::CreateResourceJSON(j);
    return spresource;
}
unsigned long Wolf::Resources::ResourceFactory::CreateMeshResource(const nlohmann::json &j) {


    return 0;
}
