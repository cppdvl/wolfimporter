#ifndef __WOLF_MTLFILEPARSER_HPP__
#define __WOLF_MTLFILEPARSER_HPP__

#include <string>
#include "wolf/import/_3dformats/_3dmateriallibraryfile.hpp"

namespace Wolf {
    namespace _3DFormats {
            
        class MTLFileParser : public _3DMaterialLibraryFile {
            
        public:
            MTLFileParser(const std::string& rrelpath) : _3DMaterialLibraryFile(rrelpath){}
            bool Serialize() override;
        };
    }
}
#endif