
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <nlohmann/json.hpp>

#include <wolf/engine/scene.hpp>
#include <wolf/engine/engine.hpp>
#include <wolf/engine/clipparser.hpp>
#include <wolf/engine/resourcemanager.hpp>

namespace Wolf::Engine {

    void startEngineWindow(const std::string configurationPath){
        
        std::ifstream i(configurationPath);
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
        auto rmi = Wolf::Engine::ResourceManager::spGetInstance();
        rmi->vRegisterResourcesInSandbox(options.defaultSandbox);

    }
    void createDefaultScene(){

    }
    Wolf::Engine::ReturnCode Init(int argc, const char**argv, std::function<void()> fn){

        //Here is where the engine starts everything
        auto options = Wolf::Cli::loadOptions(argc, argv);
        
        //Engine User fn
        setOptions(options);

        //Ok Now we have an opengl contexted screen and some resources (though they are lazy, but they are there).

        

        if(fn)fn();
        else {

        }
        

        return ReturnCode::OK;
    }

    
}
