//
// Created by User on 7/25/2020.
//

#ifndef WOLF_COMPONENT_NAME_HPP
#define WOLF_COMPONENT_NAME_HPP

#include <string>
#include <wolf/ecs/component/component.hpp>

namespace Wolf::ECS {
    class ComponentName : public Wolf::ECS::Component {
        std::string mName;
    public:
        explicit ComponentName(const std::string&);
        explicit ComponentName(const char*);

    };
}
#endif //WOLF_COMPONENT_NAME_HPP
