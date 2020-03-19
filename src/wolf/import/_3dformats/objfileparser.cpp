#include <iostream>

#include "wolf/stringutils.hpp"
#include "wolf/vectorutils.hpp"
#include "wolf/import/wavefrontutils.hpp"
#include "wolf/import/_3dformats/objfileparser.hpp"
#include "wolf/import/_3dformats/mtlfileparser.hpp"
bool Wolf::_3DFormats::OBJFileParser::Serialize()  {
    
    std::vector<float> vertices{};
    std::vector<float> texcoord{};
    std::vector<float> vnormals{};
    
    
    
    enum wavefrontstate {
        none, mtllib, o, v, vt, vn, usemtl, s, f
    };
    
    
    auto state = none;
    std::string nameofthegame{};
    std::string nameOfMaterialLibrary{};
    std::string nameoftheobject{};
    std::string nameoftheshader{};
    std::map<std::string, wavefrontstate> linetype_state{
        std::make_pair("mtllib", mtllib),
        std::make_pair("o", o),
        std::make_pair("v", v),
        std::make_pair("vt", vt),
        std::make_pair("vn", vn),
        std::make_pair("usemtl", usemtl),
        std::make_pair("s", s),
        std::make_pair("f", f)
    };
    for (auto&line:lines){
        
        if (line.empty()) continue;
        auto commandStringVector = Wolf::StringUtils::split(line,' ');
        auto keyFound = linetype_state.find(commandStringVector[0]) != linetype_state.end();
        
        if (!keyFound) continue;
        
        state = linetype_state[commandStringVector[0]];
        auto commandString = Wolf::StringUtils::join(commandStringVector,' ', 1);
        if (state == mtllib) {
            
            auto matlibraryname = FolderPath() + commandStringVector[1];
            auto materialFileParser = MTLFileParser(matlibraryname);
            auto materialOk = materialFileParser.Serialize();
            std::cout << "Material: " << FolderPath() + commandStringVector[1] <<" is  " << (materialOk?"ok":"fucked") << std::endl;
            matlibraryname__matname_mat[matlibraryname] = materialFileParser.materialname_material;

        }

        else if (state == o)  {
            
            nameoftheobject = commandStringVector[1];
            objectname__shadername_vtn[nameoftheobject] = std::map<std::string, std::vector<float>>{};
            
        }
        else if (state == usemtl){
            nameoftheshader = commandStringVector[1];
            objectname__shadername_vtn[nameoftheobject][nameoftheshader] = std::vector<float>{};
        }
        else if (state == v)
            Wolf::VectorUtils::pushvectorf(vertices, commandString, 3);
        else if (state == vn)
            Wolf::VectorUtils::pushvectorf(vnormals, commandString, 3);
        else if (state == vt)
            Wolf::VectorUtils::pushvectorf(texcoord, commandString, 2);
        else if (state == f){
            
            std::vector<unsigned int> vtxindexes{};
            std::vector<unsigned int> txcindexes{};
            std::vector<unsigned int> vnmindexes{};

            Wolf::WavefrontUtils::pushfaceindexes(vtxindexes, txcindexes, vnmindexes, commandString);
            auto&vtn = objectname__shadername_vtn[nameoftheobject][nameoftheshader];
            
            if ( vtxindexes.size() % 3) {
                std::cout << "vtxindexes is not 3x" << std::endl;
                std::exit(-1);
            }
            
            if ( txcindexes.size() % 3) {
                std::cout << "txcindexes is not 3x" << std::endl;
                std::exit(-1);
            }
            if ( vnmindexes.size() % 3) {
                std::cout << "Normals indexes are not 3x" << std::endl;
                std::exit(-1);
            }
            if ( vtxindexes.size() != txcindexes.size() || txcindexes.size() != vnmindexes.size()){
                std::cout << "Size of indexes per triangle error";
                std::exit(-1);
            }
            for ( auto pointindex = 0; pointindex < 3; ++pointindex ){
                for( auto xyzindex = 0; xyzindex < 3; ++xyzindex ) vtn.push_back( vertices[vtxindexes[pointindex] * 3 + xyzindex ] );
                for( auto xyzindex = 0; xyzindex < 2; ++xyzindex ) vtn.push_back( texcoord[txcindexes[pointindex] * 2 + xyzindex ] );
                for( auto xyzindex = 0; xyzindex < 3; ++xyzindex ) vtn.push_back( vnormals[vnmindexes[pointindex] * 3 + xyzindex ] );
            } 
        } 
        
    }
    
    return true;
}