#include <mutex>
#include <cstdlib>
#include <iostream>

#include <wolf/engine/resourcemanager.hpp>

void Wolf::Engine::ResourceManager::vRegisterResourcesInSandbox(const std::string& resourceUrl){
    auto sandboxMapping = Wolf::Engine::SandboxMapper::xGetMapping(resourceUrl);
    std::for_each(sandboxMapping.cbegin(), sandboxMapping.cend(), [&](const Wolf::Engine::SandboxBind& bind){
        auto value = xSymlinkResource(bind);
        if (value != Wolf::Engine::ResourceManagerValueReturned::Ok){
            std::cout << "Resource Mapping Error: [" << resourceUrl << "] " << bind.first << " <=> " << bind.second << std::endl;
            std::cout << "\t" << xErrorValue_sMessages[value] << std::endl;
        }
    });
}
Wolf::Engine::ResourceManagerValueReturned Wolf::Engine::ResourceManager::xSymlinkResource(const Wolf::Engine::SandboxBind& bind){
    return xSymlinkResource(bind.first, bind.second);
}
Wolf::Engine::ResourceManagerValueReturned Wolf::Engine::ResourceManager::xSymlinkResource(const std::string& alias, const std::string& resourceUrl){

            //Check the alias is not being used already
    auto bAliasFound = sAlias_xResourceAlias.find(alias) != sAlias_xResourceAlias.end();
    if (bAliasFound){
        return Wolf::Engine::ResourceManagerValueReturned::AliasAlreadyExists;
    }

            //Check if the resource exists already
    auto pathFound = sPath_spResource.find(resourceUrl) != sPath_spResource.end();
    if (!pathFound){
                /*** Check the path is valid and something ***/
        auto bIsValidUrlAndUrlExists = true; 
        if (bIsValidUrlAndUrlExists == false ){
            return Wolf::Engine::ResourceManagerValueReturned::UrlIsNotAValidResource;
        }
        sPath_spResource[resourceUrl] = nullptr ;
    }

            //Associate alias
    auto bAliasNotEmpty = !alias.empty();
    if (bAliasNotEmpty){
        sAlias_xResourceAlias[alias] = Wolf::Engine::ResourceAlias(resourceUrl, sPath_spResource[resourceUrl]);;
    }

    return Wolf::Engine::ResourceManagerValueReturned::Ok;
} //x = some custom data type (the enumeration)


bool Wolf::Engine::ResourceManager::bResourceIsRegistered(const std::string& resourceName){

    auto resFound = sAlias_xResourceAlias.find(resourceName) != sAlias_xResourceAlias.end();
    return resFound;

}
bool Wolf::Engine::ResourceManager::_bResourceStillLazy(const Wolf::Engine::ResourceAlias& url_wpresource){

    auto wpResource = url_wpresource.second;
    if (wpResource.expired()) return true;
    auto spResource = wpResource.lock(); 
    if (spResource == nullptr) return true;
    else return false;

}
Wolf::Engine::SPResource Wolf::Engine::ResourceManager::_spGetResource(const std::string& resourceName){

    //We already know this resource is registered. 
    auto url_wpresource = sAlias_xResourceAlias[resourceName];
    auto url = url_wpresource.first;

    

    return nullptr;
}

Wolf::Engine::SPResource Wolf::Engine::ResourceManager::spGetResource(const std::string& resourceName){

    auto resourceNotFound = !bResourceIsRegistered(resourceName);
    if (resourceNotFound){
        //Handle this error somehow.
        std::cout << xErrorValue_sMessages[Wolf::Engine::ResourceManagerValueReturned::InvalidResourceReferenceKey] << " " << resourceName << std::endl;
        std::exit(-1);        
    } 
    auto url_wpresource = sAlias_xResourceAlias[resourceName];
    if (_bResourceStillLazy(url_wpresource)) return _spGetResource(resourceName);
    auto spResource = url_wpresource.second.lock();
    return spResource;
}