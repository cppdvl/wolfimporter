//
// Created by User on 8/19/2020.
//

#include <wolf/resources/resourcejson.hpp>
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

        auto spResource = std::make_shared<Wolf::Resources::ResourceJSON>(url);
        return std::static_pointer_cast<Wolf::Resources::Resource>(spResource);

    } /*else if (extension == " "){

    }*/
    return nullptr;
}

