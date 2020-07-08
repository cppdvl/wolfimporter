#ifndef __WOLF_ENGINE__
#define __WOLF_ENGINE__

#include <mutex>
#include <functional>


#include <wolf/glfw/glfw.hpp>
#include <wolf/engine/scene.hpp>
#include <wolf/engine/clipparser.hpp>

//--- The following includes need to be gone some day ---//
#include <wolf/engine/resourcemanager.hpp>

namespace Wolf::Engine {

    enum class ReturnCode {
        OK,
        ERROR
    };
    Wolf::Engine::ReturnCode Init(int argc, const char ** argv, std::function<void()> fn = [](){});
    Wolf::Engine::ReturnCode Run();
    Wolf::Engine::ReturnCode Pause();
    Wolf::Engine::ReturnCode Stop();

    


    /**** This is for test purposes, should be gone some day *****/
    void setOptions(const Wolf::Cli::WolfEngineOptions&);

    struct SceneAllocationBlock{

        using SceneAllocatedCallBack = std::function<void()>; 
        SceneAllocationBlock::SceneAllocatedCallBack sceneAllocatedCallBack;

    };

    class SceneAllocator{
    };

}

#endif //__WOLF_ENGINE__