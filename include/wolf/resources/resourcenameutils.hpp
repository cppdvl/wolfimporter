//
// Created by User on 7/26/2020.
//

#ifndef WOLF_RESOURCENAMEUTILS_HPP
#define WOLF_RESOURCENAMEUTILS_HPP
#include <string>
#include <vector>
namespace Wolf::Engine {

class ResourceName : public std::vector<std::string> {
        std::vector<std::string> mAliasPath{};
        std::string mResourceAlias{};
    public:
        explicit ResourceName(std::string resourcename);
        inline const std::string& resourceAlias(){ return mResourceAlias; }
        inline const std::vector<std::string>& aliasPath(){ return mAliasPath; }


    };

}
#endif //WOLF_RESOURCENAMEUTILS_HPP
