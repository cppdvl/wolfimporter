//
// Created by User on 7/25/2020.
//

#ifndef WOLF_COMPONENT_NAME_HPP
#define WOLF_COMPONENT_NAME_HPP

#include <string>
#include <wolf/engine/ecs/component.hpp>

namespace Wolf::Engine::ECS {
    class ComponentName : public Wolf::Engine::ECS::Component {
        std::string mName;
    public:
        explicit ComponentName(const std::string&);
        explicit ComponentName(const char*);

    };
}
#endif //WOLF_COMPONENT_NAME_HPP
