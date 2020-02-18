#ifndef __WOLF_OBJFILEPARSER_H__
#define __WOLF_OBJFILEPARSER_H__

#include "wolf/import/_3dformats/_3dfileparser.hpp"
namespace Wolf {
    namespace _3DFormats {
        class OBJFileParser : public _3DFileParser{
            public:
				OBJFileParser(const std::string& rrelpath) : _3DFileParser(rrelpath){}
				bool Serialize() override;
        };
    }
}

#endif