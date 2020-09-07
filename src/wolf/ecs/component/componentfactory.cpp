//
// Created by User on 8/30/2020.
//
//T0 DISABLE ASSERT uncomment:
//#define NDEBUG
#include <cassert>

#include <wolf/resources/resourcemanager.hpp>
#include <wolf/resources/json/resourcejson.hpp>
#include <wolf/ecs/component/componentfactory.hpp>

Wolf::ECS::SPComponent
Wolf::ECS::ComponentFactory::CreateSPComponent(const std::string &keyComponentTypeString, const nlohmann::json& componentJSONORString) {

    auto checkTypeString = mapStringType.find(keyComponentTypeString) != mapStringType.end();
    auto checkJSONType = componentJSONORString.is_object() || componentJSONORString.is_string();
    assert(checkTypeString);
    assert(checkJSONType);

    auto componentType = mapStringType[keyComponentTypeString];

    //If it is not a json is a string with a reference where the json is at.
    if (componentJSONORString.is_string()){

        auto componentReferenceString = componentJSONORString.get<std::string>();
        auto spRMI = Wolf::Resources::ResourceManager::spGetInstance();
        assert(spRMI);
        auto rmi = *spRMI;
        auto spResourceJSON = std::dynamic_pointer_cast<Resources::ResourceJSON>(rmi[componentReferenceString]);
        assert(spResourceJSON);
        return CreateSPComponent(keyComponentTypeString, *spResourceJSON); //*spResourceJSON!?, yep that objetc inherits nlohmann::json.

    }

    //Ok it's a JSON.
    auto& componentJSON = componentJSONORString;
    if (componentType == ComponentType::MESH_COMPONENT){
        //Create a Mesh Component, in general terms the float buffer with data.
    } else if (componentType == ComponentType::KINEMATIC_COMPONENT){
        //Create a x, dx/dt and dv/dt matrix.
    }
    assert(false);
    return nullptr;

}