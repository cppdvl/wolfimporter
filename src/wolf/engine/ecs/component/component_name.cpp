//
// Created by User on 7/25/2020.
//

#include "wolf/engine/ecs/component/component_name.hpp"
Wolf::Engine::ECS::ComponentName::ComponentName(const char* pcName)
:
Wolf::Engine::ECS::Component(),
mName(std::string{pcName})
{

}
Wolf::Engine::ECS::ComponentName::ComponentName(const std::string& strName)
        :
        Wolf::Engine::ECS::Component(),
        mName(std::string{strName})
{

}
