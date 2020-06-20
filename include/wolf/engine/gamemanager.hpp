#ifndef _WOLF_GAMEMANAGER_
#define _WOLF_GAMEMANAGER_

#include <stack>
#include <memory>

#include <wolf/engine/scene.hpp>
#include <wolf/pttrns/singleton.hpp>

namespace Wolf::Engine {

using STKSPScene = std::stack<Wolf::Engine::SPScene>;
    
    class GameManager : public Wolf::Pttrn::Singleton<GameManager>, public Wolf::Engine::STKSPScene {

    };

}

#endif