#ifndef __WOLF_RESOURCEMANAGER__
#define __WOLF_RESOURCEMANAGER__


#include <map>
#include <set>
#include <tuple>
#include <memory>
#include <string>
#include <utility>
#include <unordered_map>

#include <wolf/engine/entity.hpp>
#include <wolf/pttrns/singleton.hpp>
#include <wolf/engine/sandboxmapper.hpp>
#include <wolf/engine/gamemanager.hpp>

namespace Wolf::Engine {
    
    class Resource {
        
    };
    
    enum class ResourceManagerValueReturned {
        Ok, 
        UrlIsNotAValidResource,
        UrlDoesNotExist,
        AliasAlreadyExists,
        InvalidResourceReferenceKey
    };
    using SPResource = std::shared_ptr<Wolf::Engine::Resource>;
    using WPResource = std::weak_ptr<Wolf::Engine::Resource>;
    using WPResources = std::set<WPResource>;
    using ResourceAlias = std::pair<std::string, Wolf::Engine::WPResource>; 
    
    class ResourceManager : public Wolf::Pttrn::Singleton<Wolf::Engine::ResourceManager> {
        
        std::unordered_map<std::string, SPResource> sPath_spResource{};
        std::unordered_map<std::string, Wolf::Engine::ResourceAlias> sAlias_xResourceAlias{};
        
        std::map<Wolf::Engine::ResourceManagerValueReturned, std::string> xErrorValue_sMessages {
            
            std::make_pair(Wolf::Engine::ResourceManagerValueReturned::Ok, "Ok"),
            std::make_pair(Wolf::Engine::ResourceManagerValueReturned::UrlIsNotAValidResource, "Url is not a valid resource"),
            std::make_pair(Wolf::Engine::ResourceManagerValueReturned::UrlDoesNotExist, "Url does not exist"),
            std::make_pair(Wolf::Engine::ResourceManagerValueReturned::InvalidResourceReferenceKey, "Invalid Resource Reference Key "),
            std::make_pair(Wolf::Engine::ResourceManagerValueReturned::AliasAlreadyExists, "Alias already in use")
            
        };
        
        /**
         * @brief      This function loads lazy resources that are not yet on memory. 
         *
         * @param[in]  <unnamed>  { parameter_description }
         *
         * @return     { description_of_the_return_value }
         */
        Wolf::Engine::SPResource _spGetResource(const std::string&);

        bool _bResourceStillLazy(const Wolf::Engine::ResourceAlias&);

        public:
        void vRegisterResourcesInSandbox(const std::string& resourceUrl);
        ResourceManagerValueReturned xSymlinkResource(const Wolf::Engine::SandboxBind& bind);
        /**
         * @brief      Assign an aliased name to a resource and lazy loads it.  
         *
         * @param[in]  resourceUrl  The resource url
         * @param[in]  alias        The alias
         * 
         * @return     true, when resourceUrl it's valid (it represents something asset-able) and the resourcename and alias are registered in lazyness. If alias already exists it or not a valid url it will return false  
         */
        ResourceManagerValueReturned xSymlinkResource(const std::string& alias, const std::string& resourceUrl);
        

        /**
         * @brief      Get a pointer to the resource referenced by the resource name
         *
         * @param[in]  resourceName  The name of the resource to get. 
         *
         * @return     On Success a shared pointer to the resource is returned. On failure nullptr is returned.
         */
        Wolf::Engine::SPResource spGetResource(const std::string& resourceName);

        /**
         * @brief      Check if a resource it's already registered. 
         *
         * @param[in]  resourceName  The resource name
         *
         * @return     If resource with is registered returns true, otherwise false.
         */
        bool bResourceIsRegistered(const std::string& resourceName);


    };

}

#endif //__WOLF_RESOURCEMANAGER__