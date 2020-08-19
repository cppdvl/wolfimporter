//
// Created by User on 8/13/2020.
//

#pragma once

#include <wolf/resources/resource.hpp>

namespace Wolf::Resources {
    class ResourceFactory {
    public:
        static SPResource CreateResource(const std::string& urlName);
    };

}