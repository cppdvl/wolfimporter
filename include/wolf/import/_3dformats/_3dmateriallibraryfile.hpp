#ifndef __WOLF_3DMATERIALLIBRARYFILE_H__
#define __WOLF_3DMATERIALLIBRARYFILE_H__

#include <map>
#include <string>
#include <vector>

#include "wolf/import/_3dformats/file.hpp"

namespace Wolf {

    namespace _3DFormats {
            
            class _3DMaterial {
            
            public:
                std::vector<float> ka{}, ks{}, kd{}, ke{}; //Ambient, Specularity, Diffuse, Emissive 
                float opacity;	
                float specularExponent; //Ns
                float opticalDensity; //Ni
            
            };
            
            class _3DMaterialLibraryFile : public _File {
            public:
                _3DMaterialLibraryFile(const std::string& rrelpath) : Wolf::_3DFormats::_File(rrelpath){}
                std::map<std::string, _3DMaterial> materialname_material{};
                virtual bool Serialize() = 0;
                    
            };
    }

}

#endif