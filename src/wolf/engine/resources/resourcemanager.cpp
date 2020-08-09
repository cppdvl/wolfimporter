
#include <mutex>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <unordered_map>

#include <wolf/import/resourceloader.hpp>
#include <wolf/engine/resources/resourcemanager.hpp>
#include <wolf/engine/resources/resourcenameutils.hpp>

Wolf::Engine::SPResource Wolf::Engine::ResourceManager::_spGetResourceFromAlias(const std::string& resourceName) {

    auto bOk = AliasIsRegistered(resourceName);
    if(!bOk){

        _assert("Resource name is not registered yet",__FILE__,__LINE__);
        assert(bOk);

    }

    auto pairUrlWPResource = mapAlias_PairUrlWPResource[resourceName];
    auto wpResource = pairUrlWPResource.second;
    auto spResource = wpResource.lock();
    if (spResource) return spResource;

    //TODO: Call a Resource Factory to Determine How to Create a Resource out of the resourcename and assign that to spResource */
    spResource = Wolf::Engine::ResourceFactory::CreateResource(pairUrlWPResource.first);
    mapUrlSPResource[pairUrlWPResource.first] = spResource;
    return spResource;

}

void Wolf::Engine::ResourceManager::BindAliasToUrl(const std::string &resourceName, const std::string &resourceUrl) {

    //Check alias is not registered yet.
    auto resourceIsNotRegistered = !AliasIsRegistered(resourceName);
    if (!resourceIsNotRegistered){
        _assert("Resource Name already registered....", __FILE__, __LINE__);
        assert(resourceIsNotRegistered);
    }

    //Check file exists.
    auto resourceUrlPath = std::filesystem::path(resourceUrl);
    auto pathIsRelative = resourceUrlPath.is_relative();
    if (pathIsRelative) resourceUrlPath = std::filesystem::absolute(resourceUrlPath);
    auto pathExists = std::filesystem::exists(resourceUrlPath);
    if (!pathExists){
        _assert("Url path does not exists", __FILE__, __LINE__);
        assert(pathExists);
    }

    //Insert into resourcemanager a url <-> empty weak pointer pair.
    mapUrlSPResource.insert(std::make_pair(resourceUrlPath.string(), nullptr));
    mapAlias_PairUrlWPResource[resourceName] = std::make_pair(resourceUrlPath.string(), mapUrlSPResource[resourceUrlPath.string()]);

}

bool Wolf::Engine::ResourceManager::AliasIsRegistered(const std::string &resourceName) {
    return mapAlias_PairUrlWPResource.find(resourceName) != mapAlias_PairUrlWPResource.end();
}

Wolf::Engine::SPResource Wolf::Engine::ResourceManager::operator[](const std::string &resourceName) {

        return _spGetResourceFromAlias(resourceName);

}