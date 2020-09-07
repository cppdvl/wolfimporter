
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <nlohmann/json.hpp>

#include <wolf/ecs/scene.hpp>
#include <wolf/engine/engine.hpp>
#include <wolf/engine/gamemanager.hpp>

#include <spdlog/spdlog.h>

namespace Wolf::Engine {
    

    void startDefaultSandBox(const std::string sandboxPath){

        auto rmi = Wolf::Resources::ResourceManager::spGetInstance();
        std::ifstream i(sandboxPath);
        if (!i){
            std::cout << "Problem Opening " << sandboxPath << std::endl;
            _assert("IO ERROR", __FILE__, __LINE__);
            assert(i);
        }
        nlohmann::json j;
        i >> j;
        auto resourceType = j["RESOURCE_TYPE"];
        auto resourceIsMapping = resourceType == "MAPPING";
        assert(resourceIsMapping);

        auto resourceData = j["RESOURCE_DATA"];

        for (auto resourceDataItem : resourceData.items()){

            auto& url = resourceDataItem.value();
            auto& alias = resourceDataItem.key();
            auto id = rmi->AddResource_JSON(url, alias);
            auto rawpointer = (*rmi)[id].get();
            spdlog::info("Added Resource [ResourceJSON] id: {:x} @0x{:x}", id, (ptrdiff_t) rawpointer);

        }

    }
    void startEngineWindow(const std::string configurationPath){
        
        std::ifstream i(configurationPath);
        if (!i) std::cout << "Problem opening " << configurationPath << std::endl;
        nlohmann::json j;
        i >> j;
        auto initConfiguration = Wolf::GLFW::GLFWInitConfiguration{

            j["glversion"]["major"],
            j["glversion"]["minor"]

        };
        Wolf::GLFW::GLFWInit(initConfiguration);

        auto glfwWindowConfiguration = Wolf::GLFW::GLFWWindowConfiguration{

            j["window"]["size"][0],
            j["window"]["size"][1],
            j["window"]["windowTitle"]

        };
        Wolf::GLFW::pWindow = Wolf::GLFW::GLFWCreateWindow(glfwWindowConfiguration);
    
    }
    void setOptions(const Wolf::Cli::WolfEngineOptions& options){

        startEngineWindow(options.defaultConfiguration);
        startDefaultSandBox(options.defaultSandbox);

    }
    void createDefaultScene(){

        auto pScene = std::make_shared<Wolf::ECS::Scene>("wolfeScene");
        auto pGameManager = Wolf::Engine::GameManager::spGetInstance();
        pGameManager.get()->push(pScene);

    }

    void startGameManager(){
        
        auto pGameManager = Wolf::Engine::GameManager::spGetInstance();

    }
    Wolf::Engine::ReturnCode Init(int argc, const char**argv, std::function<void()> fn){

        //Here is where the engine starts everything
        auto options = Wolf::Cli::loadOptions(argc, argv);
        
        //Engine User fn
        setOptions(options);

        //Generate a Game Manager

        //Ok Now we have an opengl contexted screen and some resources (though they are lazy, but they are there).
		fn();

        return ReturnCode::OK;
    }

    
}
