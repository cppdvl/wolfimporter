//
// Created by User on 7/26/2020.
//
#include <algorithm>
#include <iostream>
#include "wolf/engine/resources/resourcenameutils.hpp"
Wolf::Engine::ResourceName::ResourceName(std::string resourcename) : mResourceAlias(resourcename){

    while (true){
        auto tokenpos = resourcename.find("//");
        if (tokenpos == std::string::npos){
            break;
        }
        auto token = resourcename.substr(0,tokenpos-1);
        mAliasPath.push_back(token);
        resourcename = resourcename.substr(tokenpos + 2, resourcename.size() - tokenpos);
    }
    mAliasPath.push_back(resourcename);

    while (!mAliasPath.empty()){
        auto tmpResourceName = std::string{};
        for (auto& resourceNameToken : mAliasPath){
            tmpResourceName += resourceNameToken;
            tmpResourceName += "//";
        }
        auto lastSepPos = tmpResourceName.find_last_of("//");
        tmpResourceName = lastSepPos != std::string::npos ? tmpResourceName.substr(0, lastSepPos - 1) : tmpResourceName;
        this->push_back(tmpResourceName);
        mAliasPath.pop_back();
    }

    for (auto& _this : *this){
        std::cout << "Candidate: " << _this << std::endl;
    }
}