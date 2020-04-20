#ifndef WOLF_PARSER_OBJ
#define WOLF_PARSER_OBJ
#include "wolf/import/parser.hpp"
namespace Wolf {
    class OBJParser : public Wolf::Parser {
    public:
        virtual void* Serialize(const Wolf::File&);
    };

}
#endif //WOLF_PARSER_OBJ