#ifndef __WOLF_SCENE__
#define __WOLF_SCENE__

#include <string>
#include <memory>
#include <wolf/engine/entity.hpp>

namespace Wolf::Engine {
    
    class Scene;
    using SPScene = std::shared_ptr<Wolf::Engine::Scene>;
    
    class Scene : public Wolf::Engine::VWPEntity {
    protected:        
        unsigned long sceneId{0};              
    public:
        Scene(){
            
        }
        Scene(std::string const& resourceName);
        //calbacks
        virtual void init();
        virtual void update(unsigned int msec_delta);
        virtual void render();
        virtual void finish();
        virtual ~Scene() {}
    };

}


#endif //__WOLF_SCENE__