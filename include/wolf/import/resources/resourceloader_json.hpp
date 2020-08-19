//
// Created by User on 7/25/2020.
//

#ifndef WOLF_RESOURCELOADER_JSON_HPP
#define WOLF_RESOURCELOADER_JSON_HPP
#include <wolf/import/resourceloader.hpp>


namespace Wolf::Import{

    class ResourceLoaderJSON : public ResourceLoader {
    public:
        ResourceLoaderJSON(const std::string& resourceName, const std::string& resourceExtension) : ResourceLoader(resourceName, resourceExtension){

        }
        virtual Wolf::Resources::SPResource LoadResource() override;

    };


}


#endif //WOLF_RESOURCELOADER_JSON_HPP
