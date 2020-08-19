//
// Created by User on 7/21/2020.
//

#ifndef WOLF_RESOURCELOADER_HPP
#define WOLF_RESOURCELOADER_HPP

#include <string>
#include <wolf/resources/resourcemanager.hpp>

namespace Wolf::Import {
    class ResourceLoader {
    protected:
        enum class _ResourceTypes {
            UNDEFINED,
            JSON,
            WAVEFRONT
        };
        inline static std::map<std::string, _ResourceTypes>mapType {
           std::make_pair("json", _ResourceTypes::JSON),
           std::make_pair("obj", _ResourceTypes::WAVEFRONT)
        };
        std::string mResourcePath{};
        std::string mResourceExtension{};
        _ResourceTypes mResourceExtensionType{_ResourceTypes::UNDEFINED};

    public:
        explicit ResourceLoader(const std::string& resourceName, const std::string& resourceExtension);
        virtual Wolf::Resources::SPResource LoadResource() = 0;

    };



    using UPResourceLoader = std::unique_ptr<ResourceLoader>;
    class ResourceLoaderFactory {
    public:
        static UPResourceLoader GetResourceLoader(const std::string resourceName);
    };


}


#endif //WOLF_RESOURCELOADER_HPP
