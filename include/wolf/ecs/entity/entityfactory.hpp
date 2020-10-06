//
// Created by User on 9/7/2020.
//

#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <wolf/ecs/entity/entity.hpp>

namespace Wolf::ECS{
    class EntityFactory {
    public:
        static Wolf::ECS::SPEntity CreateEntity(const std::string& entityName, const nlohmann::json& jsn);

    };
}