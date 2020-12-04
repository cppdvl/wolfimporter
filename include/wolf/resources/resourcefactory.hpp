//
// Created by User on 8/13/2020.
//

#pragma once

#include <wolf/resources/resource.hpp>

namespace Wolf::Resources {
    class ResourceFactory {
    public:
        //Create a Resource from a file.
        static SPResource CreateResource(const std::string& urlName);

        //Create a Resource from a json.
        static SPResource CreateResource(const nlohmann::json&);



        static unsigned long CreateMeshResource(const nlohmann::json& j);
    };

}