//
// Created by User on 8/19/2020.
//
#include <iostream>
#include <wolf/ecs/entity.hpp>
#include <wolf/resources/resourcemanager.hpp>
#include <wolf/resources/json/resourcejsonvisitor.hpp>

Wolf::ECS::SPECSNode Wolf::Resources::SceneVisitor::visit(Wolf::Resources::ResourceJSON& resourceJson, const std::string, const std::string) {

    EntityVisitor entityVisitor;

    for (auto& [entityname, entityjson] : resourceJson.items()){
        auto spECSNodeEntity = entityVisitor.visit(resourceJson, entityname);
    }
    return nullptr;
}

Wolf::ECS::SPECSNode Wolf::Resources::EntityVisitor::visit(Wolf::Resources::ResourceJSON& resourceJson, const std::string entityName, const std::string) {

    auto& entity = resourceJson[entityName];
    ComponentVisitor compVisitor;

    auto pEntity = std::make_shared<Wolf::ECS::Entity>();
    if (pEntity){

        for (auto& [componenttypename, componentjson] : entity.items()){
            auto spECSNode = compVisitor.visit(resourceJson, componenttypename, entityName);

        }
        return pEntity;
    }

    return nullptr;
}

Wolf::ECS::SPECSNode Wolf::Resources::ComponentVisitor::visit(Wolf::Resources::ResourceJSON& resourceJson, const std::string componentTypeString, const std::string entityParentName) {


    if (componentTypeString == "mesh_component"){
        std::cout << "Creating a mesh component" << std::endl;
        auto spResourceManagerInstance = Wolf::Resources::ResourceManager::spGetInstance();
        auto resource = resourceJson[entityParentName][componentTypeString];
        if (resource.is_string()){
            auto resourcestring = resource.get<std::string>();
            std::cout << "Trying to get from resource manager [" << resourcestring << "] resource" << std::endl;
            auto spResource = spResourceManagerInstance->operator[](resourcestring);
        }
    }

    return nullptr;
}