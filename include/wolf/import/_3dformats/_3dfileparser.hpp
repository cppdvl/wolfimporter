#ifndef __WOLF_3DFILEPARSER_H__
#define __WOLF_3DFILEPARSER_H__


#include "wolf/import/_3dformats/_3dmateriallibraryfile.hpp"

namespace Wolf {
    namespace _3DFormats {
        
        class _3DFileParser : public Wolf::_3DFormats::_File {
            public:
                _3DFileParser(const std::string& rrelpath) : _File(rrelpath){}
                
                //Print Code for Object with a particular shader
                void DumpCode(std::string, std::string);
                
                //Get Vertex Buffer Object with Shader.
                std::vector<float> DumpCodeVector(std::string, std::string);
                
                //Get Vertex Buffer Object Map. 
                std::map<std::string, std::vector<float>> DumpCodeVectorMap(std::string);
                
                //Get Material Info
                Wolf::_3DFormats::_3DMaterial DumpMaterialInformation(std::string, std::string);

                //Parse the format.
                virtual bool Serialize() = 0;
                
            protected:
                std::map<std::string, std::map<std::string, std::vector<float>>> objectname__shadername_vtn{};
                std::map<std::string, std::map<std::string, Wolf::_3DFormats::_3DMaterial>> matlibraryname__matname_mat{};      
        };
    }
}

#endif