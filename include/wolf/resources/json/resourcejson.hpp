//
// Created by User on 8/13/2020.
//

#pragma once
#include <iostream>
#include <filesystem>
#include <wolf/resources/resource.hpp>
namespace Wolf::Resources {

    class ResourceJSON : public Resource, public nlohmann::json {
    public:
        enum class RESOURCE_TYPE{
            INVALID,
            MAPPING,
            SCENE,
            CAMERAS,
            PRIMITIVES_MESH,
            JSONOBJECT
        };

        explicit ResourceJSON(const nlohmann::json&, const std::string&);

    private:
        RESOURCE_TYPE mResourceType{RESOURCE_TYPE::INVALID};
        static inline std::unordered_map<std::string, RESOURCE_TYPE> mapStringType{
                std::make_pair("MAPPING", RESOURCE_TYPE::MAPPING),
                std::make_pair("SCENE", RESOURCE_TYPE::SCENE),
                std::make_pair("CAMERAS", RESOURCE_TYPE::CAMERAS),
                std::make_pair("PRIMITIVES_MESH", RESOURCE_TYPE::PRIMITIVES_MESH),
                std::make_pair("JSONOBJECT", RESOURCE_TYPE::JSONOBJECT)
        };
        static inline std::unordered_map<RESOURCE_TYPE, std::string> mapTypeString{
                std::make_pair(RESOURCE_TYPE::MAPPING, "MAPPING"),
                std::make_pair(RESOURCE_TYPE::SCENE, "SCENE"),
                std::make_pair(RESOURCE_TYPE::CAMERAS, "CAMERAS"),
                std::make_pair(RESOURCE_TYPE::PRIMITIVES_MESH, "PRIMITIVE_MESH"),
                std::make_pair(RESOURCE_TYPE::JSONOBJECT, "JSONOBJECT")
        };

    public:

        inline std::pair<std::string, RESOURCE_TYPE> getType(){
            return std::make_pair(mapTypeString[mResourceType], mResourceType);
        }
        ResourceJSON() = delete;
        ResourceJSON(const ResourceJSON&) = delete;
        ResourceJSON(ResourceJSON&&) = delete;
        ResourceJSON& operator=(const ResourceJSON&) = delete;
        ResourceJSON& operator=(ResourceJSON&&) = delete;

        static SPResource CreateResourceJSON(const std::string&);
        static SPResource CreateResourceJSON(const std::filesystem::path&);
        static SPResource CreateResourceJSON(const nlohmann::json&);

        void PrettyPrint(){
            std::cout << std::setw(4) << static_cast<nlohmann::json>(*this) << std::endl;
        }
    };


}