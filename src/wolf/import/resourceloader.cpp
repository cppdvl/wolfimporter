//
// Created by User on 7/21/2020.
//
#include <map>
#include <tuple>
#include <memory>
#include <algorithm>
#include <functional>
#include <filesystem>
#include "wolf/import/resourceloader.hpp"
#include "wolf/import/resources/resourceloader_json.hpp"

Wolf::Import::ResourceLoader::ResourceLoader(const std::string& resourceName, const std::string& resourceExtension) :
        mResourcePath(resourceName),
        mResourceExtension(resourceExtension),
        mResourceExtensionType(mapType[resourceExtension]){



}

Wolf::Import::UPResourceLoader Wolf::Import::ResourceLoaderFactory::GetResourceLoader(const std::string resourceName) {

    std::map<std::string, std::function<UPResourceLoader (std::string, std::string) >> extension_resourceAllocationCB{
        std::make_pair("json",  [](std::string resourceName, std::string resourceExtension){
            return std::make_unique<Wolf::Import::ResourceLoaderJSON>(resourceName, resourceExtension);
        }),
        std::make_pair("obj",   [](std::string resourceName, std::string resourceExtension){
            return std::make_unique<Wolf::Import::ResourceLoaderJSON>(resourceName, resourceExtension);
        })
    };

    auto resourceExtension = std::filesystem::path(resourceName).extension().string();
    auto nodot = [&](){

        if (resourceExtension[0] == '.'){
            resourceExtension.erase(0, 1);
        }
    };
    nodot();

    auto isBadExtension = [&](){

        if (resourceExtension.empty()) return true;
        for(std::basic_string<char>::size_type index = 0; index < resourceExtension.size(); ++index){
            unsigned char* ptr = (unsigned char*)&resourceExtension.data()[index];
            *ptr = std::tolower(*ptr);
        }

        auto notextensionfound = extension_resourceAllocationCB.find(resourceExtension) == extension_resourceAllocationCB.end();
        if (notextensionfound) return true;
        return false;
    };
    if (isBadExtension()) return nullptr;

    auto allocationCallback = extension_resourceAllocationCB[resourceExtension];
    return allocationCallback(resourceName, resourceExtension);


}
