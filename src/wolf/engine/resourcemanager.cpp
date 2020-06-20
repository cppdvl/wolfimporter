#include <mutex>
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
