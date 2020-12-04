
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
Wolf::Resources::SPResource Wolf::Resources::ResourceManager::_RetryReference(const std::string &resourceName) {

    //This manages cases where we ask for a resource named name//0 or name//elementindex
    auto resourceNameSplit = Wolf::Utils::StringUtils::split(resourceName, "//");
    if (resourceNameSplit.size()<= 1) return nullptr;

    //Ok get the index referenceelement and pop it off from.
    auto referenceelement = resourceNameSplit[resourceNameSplit.size() - 1];
    resourceNameSplit.pop_back();

    //Get the parent resource or container.
    auto resourceNameRejoined = Wolf::Utils::StringUtils::join(resourceNameSplit, "//");

    //Get the parent resource from index, if this resource doesn't exists the return nullptr;
    auto spparentresource = this[0][resourceNameRejoined]; // < == Recursion
    if (!spparentresource) return nullptr;

    //Check if this resource is a json resource. If not we are trying to reference something which is not subscriptable.
    auto spresourcejson = std::dynamic_pointer_cast<Wolf::Resources::ResourceJSON>(spparentresource);
    if (!spresourcejson) return nullptr;
    //Array must not be empty
    if (spresourcejson->empty()) return nullptr;


    //If the parent resource is a json array.
    bool arraycondition = spresourcejson->is_array();

    //If the parent resource is a json object
    bool objectcondition = spresourcejson->is_object();;//

    if (arraycondition){
        //Ok the parent resource is an array.

        //Ok check reference element is a valid index for the array:
        //1st check if its a valid integer
        auto [referenceisanumber, indexnumber] = Wolf::Utils::StringUtils::bui_isint(referenceelement);

        assert(referenceisanumber);
        //2nd check if the number is within a valid range
        assert(indexnumber < spresourcejson->size());

        /* Ok let's create the resource and let's return the json resource */
        auto jsonelement = (*spresourcejson)[indexnumber];
        auto jsonresource = Wolf::Resources::ResourceFactory::CreateResource(jsonelement);
        this->AddResource(jsonresource, resourceName);
        return this[0][resourceName];

    } else if (objectcondition) {
        //Ok the parent resource is an object.

        //let's check the referenced element is in the object
        if (spresourcejson->find(referenceelement) == spresourcejson->end()) return nullptr;
        this->AddResource(Wolf::Resources::ResourceFactory::CreateResource((*spresourcejson)[referenceelement]), resourceName);
        return this[0][resourceName];

    }

    return nullptr;

}

Wolf::Resources::SPResource Wolf::Resources::ResourceManager::operator[](const std::string &resourceName) {

    auto found = maliasmap.find(resourceName) != maliasmap.end();

    if (!found){
        //Check name
        return _RetryReference(resourceName);
    }
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
