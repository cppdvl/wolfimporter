#pragma once

#include <map>
#include <set>
#include <tuple>
#include <memory>
#include <string>
#include <utility>
#include <unordered_map>

#include <wolf/id.hpp>
#include <wolf/pttrns/singleton.hpp>
#include <wolf/resources/resource.hpp>

namespace Wolf::Resources {

    class ResourceManager : public Wolf::Pttrn::Singleton<Wolf::Resources::ResourceManager>{


        std::unordered_map<std::string, Wolf::Resources::SPResource> mapUrlSPResource{};
        std::unordered_map<std::string, Wolf::Resources::PairUrlWPResource> mapAlias_PairUrlWPResource{};

        
        /**
         * @brief      This function loads lazy resources that are not yet on memory. 
         *
         * @param[in]  <unnamed>  { parameter_description }
         *
         * @return     { description_of_the_return_value }
         */
        SPResource _spGetResourceFromAlias(const std::string&);

        /**
         * @brief      Check if a resource it's already registered.
         *
         * @param[in]  resourceName  The resource name
         *
         * @return     If resource with is registered returns true, otherwise false.
         */
        bool AliasIsRegistered(const std::string& resourceName);

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
         * @brief Access resources through resourcemanager instance and a subscript index operator: the resource alias.
         * @param alias
         * @return
         */
        SPResource operator[](const std::string& alias);


    };
    using SPResourceManager = std::shared_ptr<Wolf::Resources::ResourceManager>;

}

