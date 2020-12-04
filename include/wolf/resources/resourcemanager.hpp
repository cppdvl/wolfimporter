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


    class ResourceManager : public Wolf::Pttrn::Singleton<Wolf::Resources::ResourceManager> {

        std::unordered_map<unsigned long, SPResource> midmap{};
        std::unordered_map<std::string, SPResource> maliasmap{};

        SPResource _RetryReference(const std::string& resourceName);

public:

        unsigned long AddResource(SPResource spResource, const std::string& alias);
        unsigned long AddResource_JSON(const std::string& url, const std::string& alias);

        SPResource operator[](const std::string& alias);
        SPResource operator[](const unsigned long& id);


    };
    using SPResourceManager = std::shared_ptr<Wolf::Resources::ResourceManager>;

}

