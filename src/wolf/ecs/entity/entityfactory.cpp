//
// Created by User on 9/7/2020.
//

#include <spdlog/spdlog.h>

#include <wolf/utils/stringutils.hpp>
#include <wolf/ecs/entity/entityfactory.hpp>
#include <wolf/resources/resourcemanager.hpp>
#include <wolf/resources/json/resourcejson.hpp>
#include <wolf/ecs/component/componentfactory.hpp>



Wolf::ECS::SPEntity Wolf::ECS::EntityFactory::CreateEntity(const std::string &entityName, const nlohmann::json &jsn) {

    auto spEntity = std::make_shared<Wolf::ECS::Entity>();

    auto entityValueIsString = jsn.is_string();
    if (entityValueIsString){

        auto externalReferenceString = jsn.get<std::string>();
        spdlog::info("Creating entity with an inderected reference: {:s} : {:s}", entityName, externalReferenceString);
        auto isComposedString = Wolf::Utils::StringUtils::resolveStringType(externalReferenceString) == Wolf::Utils::StringUtils::WolfStringTypes::COMPOSED_NAME;

        if (isComposedString){

            spdlog::info("{:s} is a composed string", externalReferenceString);
            auto rmi = *(Wolf::Resources::ResourceManager::spGetInstance());
            auto spResource = rmi[externalReferenceString];
            auto spResourceJSON = std::dynamic_pointer_cast<Wolf::Resources::ResourceJSON>(spResource);
            return CreateEntity(entityName, *spResourceJSON);

        } else {

            spdlog::critical("{:s} is not a composed string ", externalReferenceString);

        }
    }
    assert (jsn.is_object());

    for (auto& [componentTypeString, componentJson] : jsn.items()){

        auto spComponent = Wolf::ECS::ComponentFactory::CreateComponent(componentTypeString, componentJson);
        assert(spComponent);
        spEntity->emplace_back(spComponent);

    }

    return spEntity;

}
