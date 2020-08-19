//
// Created by User on 8/13/2020.
//

#pragma once
#include <wolf/resources/resource.hpp>
namespace Wolf::Resources {

    class ResourceJSON : public Resource {
    public:
        enum class RESOURCE_TYPE{
            INVALID,
            MAPPING,
            SCENE,
            CAMERA,
            PRIMITIVES_MESH
        };
    private:
        RESOURCE_TYPE resourceType{RESOURCE_TYPE::INVALID};
        static inline std::unordered_map<std::string, RESOURCE_TYPE> mapStringType{
                std::make_pair("MAPPING", RESOURCE_TYPE::MAPPING),
                std::make_pair("SCENE", RESOURCE_TYPE::SCENE),
                std::make_pair("CAMERA", RESOURCE_TYPE::CAMERA),
                std::make_pair("PRIMITIVES_MESH", RESOURCE_TYPE::PRIMITIVES_MESH)
        };
        static inline std::unordered_map<RESOURCE_TYPE, std::string> mapTypeString{
                std::make_pair(RESOURCE_TYPE::MAPPING, "MAPPING"),
                std::make_pair(RESOURCE_TYPE::SCENE, "SCENE"),
                std::make_pair(RESOURCE_TYPE::CAMERA, "CAMERA"),
                std::make_pair(RESOURCE_TYPE::PRIMITIVES_MESH, "PRIMITIVE_MESH")
        };

    public:

        ResourceJSON() = delete;
        ResourceJSON(const ResourceJSON&) = delete;
        ResourceJSON(ResourceJSON&&) = delete;
        ResourceJSON& operator=(const ResourceJSON&) = default;

        ResourceJSON& operator=(ResourceJSON&&) = default;
        ResourceJSON(const std::string&);

        nlohmann::json resourceData{};
        inline std::pair<std::string, RESOURCE_TYPE> getType(){

            return std::make_pair(mapTypeString[resourceType], resourceType);
        }
    };


}