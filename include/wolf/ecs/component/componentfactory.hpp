//
// Created by User on 8/30/2020.
//

#pragma once
#include <wolf/ecs/component/component.hpp>
namespace Wolf::ECS {
    class ComponentFactory {
        enum class ComponentType {
            MESH_COMPONENT,
            KINEMATIC_COMPONENT
        };
        std::map<std::string, Wolf::ECS::ComponentFactory::ComponentType> mapStringType {
                std::make_pair("mesh_component", ComponentType::MESH_COMPONENT),
                std::make_pair("kinematic_component", ComponentType::KINEMATIC_COMPONENT)

        };
    public:

        /*!
         * @brief create a component using the component type and some string.
         * @return
         */
        Wolf::ECS::SPComponent CreateSPComponent(const std::string &keyComponentTypeString, const nlohmann::json&);
        SPComponent Create();

    };
}
