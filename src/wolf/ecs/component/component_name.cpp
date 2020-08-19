//
// Created by User on 7/25/2020.
//

#include <wolf/ecs/component/component_name.hpp>
Wolf::ECS::ComponentName::ComponentName(const char* pcName)
:
Wolf::ECS::Component(),
mName(std::string{pcName})
{

}
Wolf::ECS::ComponentName::ComponentName(const std::string& strName)
:
Wolf::ECS::Component(),
mName(std::string{strName})
{

}
