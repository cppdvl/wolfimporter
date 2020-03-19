#ifndef __WOLF_MTLFILEPARSER_HPP__
#define __WOLF_MTLFILEPARSER_HPP__

#include <string>
#include "wolf/import/_3dformats/_3dmateriallibraryfile.hpp"

namespace Wolf {
    namespace _3DFormats {
            
        class MTLFileParser : public _3DMaterialLibraryFile {
        protected:
            std::string mtlfilename{};
        public:
            MTLFileParser(const std::string& rrelpath, const std::string& materialFileName) : _3DMaterialLibraryFile(rrelpath, materialFileName), mtlfilename(rrelpath+materialFileName){}
            MTLFileParser(const std::string& rrelpath) : _3DMaterialLibraryFile(rrelpath), mtlfilename(rrelpath) {}
            bool Serialize() override;

        };
    }
}
#endif