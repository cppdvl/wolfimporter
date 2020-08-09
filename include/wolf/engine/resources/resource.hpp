//
// Created by User on 7/26/2020.
//

#pragma once

#include <nlohmann/json.hpp>
#include <wolf/engine/id.hpp>
namespace Wolf::Engine {

    class Resource{
    protected:

        Wolf::Engine::ID mID{};

    public:
        Resource(){}

    };

    using SPResource = std::shared_ptr<Wolf::Engine::Resource>;
    using WPResource = std::weak_ptr<Wolf::Engine::Resource>;
    using PairUrlWPResource = std::pair<std::string, WPResource>;

class ResourceJSON : public Resource {
    enum class RESOURCE_TYPE{
        INVALID,
        MAPPING,
        SCENE,
        CAMERA,
        PRIMITIVES_MESH

    };

    RESOURCE_TYPE resourceType{RESOURCE_TYPE::INVALID};
    static inline std::unordered_map<std::string, RESOURCE_TYPE> mapStringType{
        std::make_pair("MAPPING", RESOURCE_TYPE::MAPPING),
        std::make_pair("SCENE", RESOURCE_TYPE::SCENE),
        std::make_pair("CAMERA", RESOURCE_TYPE::CAMERA),
        std::make_pair("PRIMITIVES_MESH", RESOURCE_TYPE::PRIMITIVES_MESH)
    };

    public:

        ResourceJSON() = delete;
        ResourceJSON(const ResourceJSON&) = delete;
        ResourceJSON(ResourceJSON&&) = delete;
        ResourceJSON& operator=(const ResourceJSON&) = default;

        ResourceJSON& operator=(ResourceJSON&&) = default;
        ResourceJSON(const std::string&);

        nlohmann::json resourceData{};

};

    class ResourceFactory {
    public:
        static SPResource CreateResource(const std::string& urlName);
    };

}


