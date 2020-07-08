#ifndef _WOLF_GAMEMANAGER_
#define _WOLF_GAMEMANAGER_

#include <stack>
#include <memory>

#include <wolf/engine/scene.hpp>
#include <wolf/pttrns/singleton.hpp>

namespace Wolf::Engine {

using STKSPScene = std::stack<Wolf::Engine::SPScene>;
    
    class GameManager : public Wolf::Pttrn::Singleton<GameManager>, public Wolf::Engine::STKSPScene {
        
        public:
        void push(const Wolf::Engine::SPScene&elem){
            
            Wolf::Engine::STKSPScene::push(elem);
            //We need to tell subscribers this has happened, we need to implement the signal slot pattern

            
        }
    };

}

#endif