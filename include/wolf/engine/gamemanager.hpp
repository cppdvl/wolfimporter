#pragma once
#include <stack>
#include <memory>

#include <wolf/ecs/scene.hpp>
#include <wolf/pttrns/singleton.hpp>

namespace Wolf::Engine {

    using STKSPScene = std::stack<Wolf::ECS::SPScene>;
    class GameManager : public Wolf::Pttrn::Singleton<GameManager>, public Wolf::Engine::STKSPScene {
    };

}

