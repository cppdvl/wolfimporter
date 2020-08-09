#ifndef __WOLF_ENTITY__
#define __WOLF_ENTITY__
#include <memory>
#include <vector>

namespace Wolf::Engine::ECS {
    class Entity {
            
    };
    using WPEntity  = std::weak_ptr<Wolf::Engine::ECS::Entity>;
    using VWPEntity = std::vector<WPEntity>;
}
#endif //__WOLF_ENTITY__ 