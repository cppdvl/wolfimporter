//
// Created by User on 8/13/2020.
//

#ifndef WOLF_SCENEBUILDER_HPP
#define WOLF_SCENEBUILDER_HPP
#include <wolf/ecs/scene.hpp>
#include <wolf/resources/json/resourcejson.hpp>
namespace Wolf::ECS {

    class SceneBuilder {
        static void AddEntity(Wolf::ECS::Scene &scn, const std::string entityName, const nlohmann::json jsn);
    public:
        static void BuildScene(Wolf::ECS::Scene&, const Wolf::Resources::ResourceJSON& );
    };
}


#endif //WOLF_SCENEBUILDER_HPP
