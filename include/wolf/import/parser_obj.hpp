#ifndef WOLF_PARSER_OBJ
#define WOLF_PARSER_OBJ
#include "wolf/import/parser.hpp"
namespace Wolf {
    class OBJParser : public Wolf::Parser {
    public:
        virtual std::tuple<const nlohmann::json, const std::vector<float>> Serialize(const Wolf::File& file) override;
    };

}
#endif //WOLF_PARSER_OBJ