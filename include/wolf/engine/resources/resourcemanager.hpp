#pragma once

#include <map>
#include <set>
#include <tuple>
#include <memory>
#include <string>
#include <utility>
#include <unordered_map>

#include <wolf/engine/id.hpp>
#include <wolf/pttrns/singleton.hpp>
#include <wolf/engine/ecs/entity.hpp>
#include <wolf/engine/gamemanager.hpp>
#include <wolf/engine/sandboxmapper.hpp>
#include <wolf/engine/resources/resource.hpp>

namespace Wolf::Engine {

    class ResourceManager : public Wolf::Pttrn::Singleton<Wolf::Engine::ResourceManager>{


        std::unordered_map<std::string, Wolf::Engine::SPResource> mapUrlSPResource{};
        std::unordered_map<std::string, Wolf::Engine::PairUrlWPResource> mapAlias_PairUrlWPResource{};

        
        /**
         * @brief      This function loads lazy resources that are not yet on memory. 
         *
         * @param[in]  <unnamed>  { parameter_description }
         *
         * @return     { description_of_the_return_value }
         */
        SPResource _spGetResourceFromAlias(const std::string&);

        public:

        /**
         * @brief      Assign an aliased name to a resource and lazy loads it.  
         *
         * @param[in]  resourceUrl  The resource url
         * @param[in]  resourceName The alias
         * 
         * @return     true, when resourceUrl it's valid (it represents something asset-able) and the resourcename and alias are registered in lazyness. If alias already exists it or not a valid url it will return false  
         */
        void BindAliasToUrl(const std::string& resourceName, const std::string& resourceUrl);

        /**
         * @brief      Check if a resource it's already registered. 
         *
         * @param[in]  resourceName  The resource name
         *
         * @return     If resource with is registered returns true, otherwise false.
         */
        bool AliasIsRegistered(const std::string& resourceName);

        /**
         * @brief Access resources through resourcemanager instance and a subscript index operator: the resource alias.
         * @param alias
         * @return
         */
        SPResource operator[](const std::string& alias);


    };

}

