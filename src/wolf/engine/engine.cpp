
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <signalslot.h>
#include <nlohmann/json.hpp>

#include <wolf/engine/scene.hpp>
#include <wolf/engine/engine.hpp>
#include <wolf/engine/clipparser.hpp>
#include <wolf/engine/resources/resourcemanager.hpp>

namespace Wolf::Engine {
    

    void startDefaultSandBox(const std::string sandboxPath){

        auto rmi = Wolf::Engine::ResourceManager::spGetInstance();
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
        if (!resourceIsMapping){
            std::cout << "Resource Type of " << sandboxPath << std::endl;
            _assert("Resource Type Not MAPPING", __FILE__, __LINE__);
            assert(resourceIsMapping);
        }
        auto resourceData = j["RESOURCE_DATA"];
        for (auto resourceDataItem : resourceData.items()){
            rmi->BindAliasToUrl(resourceDataItem.key(), resourceDataItem.value());
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

        auto pScene = std::make_shared<Wolf::Engine::Scene>("wolfeScene");
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
