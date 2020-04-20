#include <string>
#include <vector>
#include <sstream>
#include "wolf/utils/stringutils.hpp"
#include "wolf/utils/wavefrontutils.hpp"
namespace Wolf{
    namespace WavefrontUtils {

        

        
    OBJData CompileOBJ(
        std::string objpath
        ){

        
        std::vector<std::map<std::string, glm::vec3>>& matdictionaryvector;
        std::vector<std::string>& texturenamevector;
        OBJData objdata{};
        std::vector<unsigned long>Compile
        Wolf::_3DFormats::OBJFileParser objdata("Objects/wolf/fuhrercube.obj");
        objdata.Serialize();

        auto geometryData = objdata.DumpCodeVectorMap("Cube");    
        auto geometryDataKeys = Wolf::MapUtils::keys(geometryData);
        std::for_each(geometryDataKeys.begin(), geometryDataKeys.end(),
            [&](auto&p){
                std::cout << std::endl << "Generating OpenGl vao's and vbo's for material: " << p << std::endl;
                auto dataVector = objdata.DumpCodeVector("Cube", p);
                auto dataVectorPtr = dataVector.data();
                auto dataVectorSz = dataVector.size();
                auto matInfo = objdata.DumpMaterialInformation("Objects/wolf/fuhrercube.mtl",p);

                auto materialDictionary = std::map<std::string, glm::vec3>{
                    std::make_pair("kd", matInfo.kd),
                    std::make_pair("ka", matInfo.ka),
                    std::make_pair("ke", matInfo.ke),
                    std::make_pair("ks", matInfo.ks),
                    std::make_pair("op_se_od", matInfo.op_se_od)
                };
                std::cout << "Mat : " << p << " " << matInfo.kd.x << " " << matInfo.kd.y << " " << matInfo.kd.z << std::endl;
                od.MtlData.push_back(materialDictionary);

                std::cout << "Mat : " << p << " pushing texture " << matInfo.texturefile << std::endl;
                texturenamevector.push_back(matInfo.texturefile);

                std::cout << "Mat : " << p << " has " << (dataVectorSz >> 3) <<  " vertices" << std::endl;
                auto texturenamevectorsz = texturenamevector.size();
                if (texturenamevector[texturenamevectorsz - 1].empty() == false) std::cout << "Mat : " << p << " has texture " << texturenamevector[texturenamevectorsz - 1] << std::endl; 

                unsigned int vbo; 
                unsigned int vao;
                glGenVertexArrays(1, &vao);
                glGenBuffers(1, &vbo);

        //-- Grab Vao --/
                glBindVertexArray(vao);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //-- VBO Header --/
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataVector.size(), dataVectorPtr, GL_STATIC_DRAW);
        //-- Vertex --/
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        //-- Texture Coordinat
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        //-- Normal --/
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        //-- Release Vao --/
                glBindVertexArray(0);

        //Number of vertices
                auto nvertices = dataVector.size() / 8;

                vaovector.push_back(vao);
                vbovector.push_back(vbo);
                vertexcount.push_back(nvertices);
            });

    }

}