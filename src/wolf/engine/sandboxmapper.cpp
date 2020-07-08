#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <wolf/engine/sandboxmapper.hpp>


Wolf::Engine::SandboxMapping Wolf::Engine::SandboxMapper::xGetMapping(const std::string &path){

    auto bExceptional = false;
    std::ifstream i(path);
    if (!i) std::cout << "Problem Opening " << path << std::endl;
    nlohmann::json j;
    i >> j;
    
    bExceptional = j.find("RESOURCE_TYPE") == j.end() || j.find("RESOURCE_DATA") == j.end();
    auto sandboxMap = Wolf::Engine::SandboxMapping{};
    
    try {
        if (bExceptional) throw;
        auto jresource_data = j["RESOURCE_DATA"];
        for(auto& jmap : jresource_data.items()) sandboxMap.push_back(std::make_pair(jmap.key(), jmap.value()));
        
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
        std::cout << "Attempting to return json mapped resources failed." << std::endl;
        std::cout << std::setw(4) << j << std::endl;

    }
    
    return sandboxMap;
    
    
}
    