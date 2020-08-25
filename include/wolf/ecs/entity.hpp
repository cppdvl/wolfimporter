#ifndef __WOLF_ENTITY__
#define __WOLF_ENTITY__

class Component;

class Component;

#include <memory>
#include <vector>
#include <wolf/ecs/component/component.hpp>

namespace Wolf::ECS {

    class Entity : public ECSNode, std::vector<Wolf::ECS::SPComponent>{
    };
    using WPEntity  = std::weak_ptr<Wolf::ECS::Entity>;
    using VWPEntity = std::vector<WPEntity>;
}
#endif //__WOLF_ENTITY__ 