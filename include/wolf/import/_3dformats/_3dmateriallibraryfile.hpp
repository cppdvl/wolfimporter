#ifndef __WOLF_3DMATERIALLIBRARYFILE_H__
#define __WOLF_3DMATERIALLIBRARYFILE_H__

#include <map>
#include <string>
#include <vector>

#include "wolf/import/_3dformats/file.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Wolf {

    namespace _3DFormats {
            
            class _3DMaterial {
                
            public:

                glm::vec3 ka{}, ks{}, kd{}, ke{}; //Ambient, Specularity, Diffuse, Emissive 
                glm::vec3 op_se_od; //float opacity;float specularExponent; //Ns float opticalDensity; //Ni
                std::string texturefile;  

            };
            
            class _3DMaterialLibraryFile : public _File {
            public:
                _3DMaterialLibraryFile(const std::string& rrelpath, const std::string& filename) : Wolf::_3DFormats::_File(rrelpath, filename){}
                _3DMaterialLibraryFile(const std::string& rrelpath) : Wolf::_3DFormats::_File(rrelpath) {}
                std::map<std::string, _3DMaterial> materialname_material{};
                virtual bool Serialize() = 0;
                    
            };
    }

}

#endif