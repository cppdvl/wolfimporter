#ifndef __WOLF_SCENE__
#define __WOLF_SCENE__

#include <string>
#include <memory>
#include <wolf/engine/entity.hpp>

namespace Wolf::Engine {
    
    class Scene;
    using SPScene = std::shared_ptr<Wolf::Engine::Scene>;
    
    class Scene {
        
        std::vector<std::weak_ptr<Wolf::Engine::Entity>> entities{};
                

    public:
        static SPScene bBuildSceneOutOfResource(std::string const& resourceName);
        //calbacks
        virtual void init();
        virtual void update(unsigned int msec_delta);
        virtual void render();
        virtual void finish();

    };

}


#endif //__WOLF_SCENE__