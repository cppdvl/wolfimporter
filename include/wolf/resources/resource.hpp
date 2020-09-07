//
// Created by User on 7/26/2020.
//

#pragma once

#include <nlohmann/json.hpp>
#include <wolf/id.hpp>
namespace Wolf::Resources {

    class Resource{
    protected:

        Wolf::ID mID{};

    public:
        Resource(){}
        virtual unsigned long getId() { return mID.getId(); }
    };

    using SPResource = std::shared_ptr<Wolf::Resources::Resource>;
    using WPResource = std::weak_ptr<Wolf::Resources::Resource>;
    using PairUrlWPResource = std::pair<std::string, WPResource>;



}


