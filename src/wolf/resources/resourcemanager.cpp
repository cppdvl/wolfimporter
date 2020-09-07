
#include <mutex>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <unordered_map>

#include <wolf/utils/stringutils.hpp>
#include <wolf/resources/resourcemanager.hpp>
#include <wolf/resources/resourcefactory.hpp>
#include <wolf/resources/json/resourcejson.hpp>




unsigned long Wolf::Resources::ResourceManager::AddResource(SPResource spResource, const std::string& alias) {

    //Check alias is not already added.
    auto aliasnotfound = maliasmap.find(alias) == maliasmap.end();
    assert(aliasnotfound);

    //Get the Resource Id which is the id to index in the resource manager.
    auto id = spResource->getId();

    //Add in both dictionaries
    maliasmap[alias] = spResource;
    midmap[id] = spResource;

    //return the id of the resource.
    return id;

}

Wolf::Resources::SPResource Wolf::Resources::ResourceManager::operator[](const std::string &resourceName) {

        auto found = maliasmap.find(resourceName) != maliasmap.end();
        assert(found);
        auto spresource = maliasmap[resourceName];
        return spresource;

}

unsigned long Wolf::Resources::ResourceManager::AddResource_JSON(const std::string &url, const std::string& alias) {

    auto spResource = Wolf::Resources::ResourceFactory::CreateResource(url);
    return this->AddResource(spResource, alias);

}

Wolf::Resources::SPResource Wolf::Resources::ResourceManager::operator[](const unsigned long &id) {

    auto idfound = midmap.find(id) != midmap.end();
    assert(idfound);
    auto spresource = midmap[id];
    return spresource;

}
