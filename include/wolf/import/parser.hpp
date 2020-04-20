#ifndef WOLF_PARSER 
#define WOLF_PARSER

#include "wolf/file/file.hpp"

namespace Wolf {

    class Parser {
    public:
        virtual void* Serialize(const Wolf::File&) = 0;
    };
    
}
#endif //WOLF_PARSER
