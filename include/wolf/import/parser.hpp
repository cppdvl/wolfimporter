#ifndef WOLF_PARSER 
#define WOLF_PARSER

#include <tuple>

#include <vector>

#include <nlohmann/json.hpp>

#include "wolf/file/file.hpp"

namespace Wolf {

    class Parser {
    public:
        virtual std::tuple<const nlohmann::json, const std::vector<float>> Serialize(const Wolf::File&) = 0;
    };
    
}
#endif //WOLF_PARSER
