#ifndef __WOLF_SCENE__
#define __WOLF_SCENE__

#include <string>
#include <memory>
#include <wolf/ecs/entity.hpp>

namespace Wolf::ECS {
    
class Scene : public Wolf::ECS::ECSNode{
    protected:
        Wolf::ECS::VWPEntity mEntities;
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

    using SPScene = std::shared_ptr<Wolf::ECS::Scene>;

}


#endif //__WOLF_SCENE__