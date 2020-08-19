//
// Created by User on 7/25/2020.
//

#ifndef WOLF_COMPONENT_HPP
#define WOLF_COMPONENT_HPP

#include <memory>
#include <vector>
#include <wolf/id.hpp>

namespace Wolf::ECS {

    class Component : public Wolf::ID {
    public:
        Component(const unsigned int& resourceId = 0);
    protected:
        unsigned int mResourceId{0};
    };

    using WPComponent = std::weak_ptr<Wolf::ECS::Component>;
    using SPComponent = std::shared_ptr<Wolf::ECS::Component>;
    using VWPComponent = std::vector<WPComponent>;
}
#endif //WOLF_COMPONENT_HPP
