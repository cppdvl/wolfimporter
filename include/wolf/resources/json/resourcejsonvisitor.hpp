//
// Created by User on 8/19/2020.
//
#pragma once
#include <wolf/ecs/ecsnode.hpp>
#include <wolf/resources/json/resourcejson.hpp>

namespace Wolf::Resources{

    class IResourceJSONVisitor {
    public:
        virtual Wolf::ECS::SPECSNode visit(Wolf::Resources::ResourceJSON&, const std::string, const std::string) = 0;
    };
    class SceneVisitor : public IResourceJSONVisitor {
    public:
        virtual Wolf::ECS::SPECSNode visit(Wolf::Resources::ResourceJSON& resourceJson, const std::string nonechild = std::string{}, const std::string noneparent = std::string{});
    };
    class EntityVisitor : public IResourceJSONVisitor {
    public:
        virtual Wolf::ECS::SPECSNode visit(Wolf::Resources::ResourceJSON& resourceJson, const std::string entityName, const std::string noneparent = std::string{});
    };
    class ComponentVisitor : public IResourceJSONVisitor {
    public:
        virtual Wolf::ECS::SPECSNode visit(Wolf::Resources::ResourceJSON& resourceJson, const std::string componentTypeString, const std::string entityParentName);
    };
}



