//
// Created by User on 8/13/2020.
//

#include "scenebuilder.hpp"

void Wolf::ECS::SceneBuilder::AddEntity(Wolf::ECS::Scene &scn, const std::string entityName, nlohmann::json jsnEntity) {

    auto entity = Wolf::ECS::Entity{};

    for ( auto& [componentName, component] : jsnEntity.items()){

    }

}

void Wolf::ECS::SceneBuilder::BuildScene(Wolf::ECS::Scene &scn, const Wolf::Resources::ResourceJSON & resjsn) {

    auto& entities = resjsn.resourceData;

    for (auto& [entityname, jsnentity] : entities.items()){
        Wolf::ECS::SceneBuilder::AddEntity(scn, entityname, jsnentity);
    }

}
