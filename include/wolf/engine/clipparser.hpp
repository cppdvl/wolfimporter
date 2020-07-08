#ifndef __WOLF_CLIPARSER__
#define __WOLF_CLIPARSER__
#include <string>
namespace Wolf::Cli {
    struct WolfEngineOptions
    {
        std::string defaultConfiguration{"wolfengine/Resources/json/default.configuration.json"};
        std::string defaultSandbox{"wolfengine/Resources/json/default.sandbox.json"};
    };

    const WolfEngineOptions loadOptions(int argc, const char ** argv);
    
}
#endif //__WOLF_CLIPARSER__