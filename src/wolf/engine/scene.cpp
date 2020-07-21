#include <memory>
#include <cstdlib>
#include <fstream>
#include <nlohmann/json.hpp>

#include <wolf/engine/scene.hpp>
#include <wolf/engine/resourcemanager.hpp>

Wolf::Engine::Scene::Scene(std::string const& resourceName){

    auto rmi = Wolf::Engine::ResourceManager::spGetInstance();
    
    //This is a default Scene.
    auto sceneResource = rmi->spGetResource(resourceName);


}

void Wolf::Engine::Scene::init(){




}
void Wolf::Engine::Scene::update(unsigned int msec_data){

}
void Wolf::Engine::Scene::render(){

}
void Wolf::Engine::Scene::finish(){
    
}