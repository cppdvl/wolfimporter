//
// Created by User on 7/25/2020.
//

#ifndef WOLF_COMPONENT_HPP
#define WOLF_COMPONENT_HPP

#include <map>
#include <memory>
#include <vector>
#include <wolf/ecs/ecsnode.hpp>

namespace Wolf::ECS {

    class Component : public Wolf::ECS::ECSNode {

    public:
        Component(const unsigned int& resourceId = 0);
    protected:
        unsigned int mResourceId{0};

    };
    using SPComponent = std::shared_ptr<Wolf::ECS::Component>;



}
#endif //WOLF_COMPONENT_HPP
