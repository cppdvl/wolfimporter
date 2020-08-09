//
// Created by User on 7/25/2020.
//

#ifndef WOLF_COMPONENT_HPP
#define WOLF_COMPONENT_HPP

#include <memory>
#include <vector>
#include <wolf/engine/id.hpp>
#include <wolf/engine/resources/resourcemanager.hpp>

namespace Wolf::Engine::ECS{

    class Component : public Wolf::Engine::ID {
    public:
        Component(const unsigned int& resourceId = 0);
    protected:
        unsigned int mResourceId{0};
    };

    using WPComponent = std::weak_ptr<Wolf::Engine::ECS::Component>;
    using SPComponent = std::shared_ptr<Wolf::Engine::ECS::Component>;
    using VWPComponent = std::vector<WPComponent>;
}
#endif //WOLF_COMPONENT_HPP
