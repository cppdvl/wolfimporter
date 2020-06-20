#ifndef __WOLF_SANDBOXMAPPER__
#define __WOLF_SANDBOXMAPPER__
#include <vector>
#include <string>
#include <utility>
namespace Wolf::Engine {

    using SandboxBind = std::pair<std::string, std::string>;
    using SandboxMapping = std::vector<SandboxBind>;  
    class SandboxMapper {
    public:
        /**
         * @brief      Get a mapping of url <-> alias bindings from a json.
         *
         * @param[in]  path  The json file path.
         *
         * @return     The mapping.
         */
        static SandboxMapping xGetMapping(const std::string& path);

    };

}

#endif //__WOLF_SANDBOXMAPPER__