#ifndef __WOLF_ENTITY__
#define __WOLF_ENTITY__
#include <memory>
#include <vector>

namespace Wolf::Engine {
    class Entity {
            
    };
    using WPEntity  = std::weak_ptr<Wolf::Engine::Entity>;
    using VWPEntity = std::vector<WPEntity>;
}
#endif //__WOLF_ENTITY__ 