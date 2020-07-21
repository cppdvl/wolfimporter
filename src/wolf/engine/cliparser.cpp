#include <filesystem>   // std::filesystem
#include <functional>   // std::function
#include <iostream>     // std::cout, std::endl
#include <map>          // std::map
#include <memory>       // std::unique_ptr
#include <sstream>      // std::stringstream
#include <string_view>  // std::string_view
#include <variant>      // std::variant
#include <vector>       // std::vector

#include <wolf/engine/clipparser.hpp>

using namespace std;
namespace Wolf::Cli{
    template <class Opts>
    struct CmdOpts : Opts
    {
        using MyProp = std::variant<string Opts::*, int Opts::*, double Opts::*, bool Opts::*>;
        using MyArg = std::pair<
        std::string, //the name of the property
        MyProp //the property itself
        >;
        ~CmdOpts() = default;

        Opts parse(int argc, const char* argv[])
        {
            vector<string_view> vargv(argv, argv+argc);
            for (int idx = 0; idx < argc; ++idx)
                for (auto& cbk : callbacks)
                    cbk.second(idx, vargv);

            return static_cast<Opts>(*this);
        }

        static unique_ptr<CmdOpts> Create(std::initializer_list<MyArg> args)
        {
            auto cmdOpts = unique_ptr<CmdOpts>(new CmdOpts());
            for (auto arg : args) cmdOpts->register_callback(arg);
            return cmdOpts;
        }

    private:
        using callback_t = function<void(int, const vector<string_view>&)>;
        map<string, callback_t> callbacks;

        CmdOpts() = default;
        CmdOpts(const CmdOpts&) = delete;
        CmdOpts(CmdOpts&&) = delete;
        CmdOpts& operator=(const CmdOpts&) = delete;
        CmdOpts& operator=(CmdOpts&&) = delete;

        auto register_callback(string name, MyProp prop)
        {
            callbacks[name] = [this, name, prop](int idx, const vector<string_view>& argv)
            {
                if (argv[idx] == name)
                {
                    std::visit(
                        [this, idx, &argv](auto&& arg)
                        {
                            auto idx_sz = static_cast<std::size_t>(idx);
                            if (idx_sz < argv.size() - 1)
                            {
                                stringstream value;
                                value << argv[idx+1];
                                value >> this->*arg;
                            }
                        },
                        prop);
                }
            };
        };
        auto register_callback(MyArg p) { return register_callback(p.first, p.second); }

    };

    const WolfEngineOptions loadOptions(int argc, const char** argv)
    {

        auto parser = CmdOpts<WolfEngineOptions>::Create({
            {"--defaultConfiguration", &WolfEngineOptions::defaultConfiguration},
            {"--defaultSandbox", &WolfEngineOptions::defaultSandbox}});

        auto wolfEngineOptions = parser->parse(argc, argv);

        std::cout << "Configuration = " << wolfEngineOptions.defaultConfiguration << endl;
        std::cout << "Resources = " << wolfEngineOptions.defaultSandbox << endl;

#if defined(_WIN32) || defined(_WIN64)

#ifndef NDEBUG
        std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
        wolfEngineOptions.defaultConfiguration = std::filesystem::absolute(wolfEngineOptions.defaultConfiguration).string();
        wolfEngineOptions.defaultSandbox = std::filesystem::absolute(wolfEngineOptions.defaultSandbox).string();
#endif
#endif

        return wolfEngineOptions;
    }

}

























