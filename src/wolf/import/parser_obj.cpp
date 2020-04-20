#include "wolf/import/parser_obj.hpp"
#include <nlohmann/json.hpp>

#include <map>
#include <tuple>

#include <memory>
#include <string>
#include <vector>

#include <function>

using json = nlohmann::json;
std::array<unsigned int, 3> GenerateVTNArray(const std::string& triangleVertexVTNKey){

    auto vstring_v_t_n = Wolf::StringUtils::split(triangleVertexVTNKey,'/');
    auto arruint_v_t_n = std::array<unsigned int, 3>{0u, 0u, 0u};
    
    std::stringstream{v_t_n[0]} >> arruint_v_t_n[0]; 
    arruint_v_t_n[0]--;
    std::stringstream{v_t_n[1]} >> arruint_v_t_n[1]; 
    arruint_v_t_n[1]--;
    std::stringstream{v_t_n[2]} >> arruint_v_t_n[2]; 
    arruint_v_t_n[2]--;

    return arruint_v_t_n;

}
const json MtlParser(const Wolf::File& file){

    using pMtlParseFunction = std::function<void(const std::vector<std::string>&)>; 
    //Declare
    struct {  
        json jsonData{json::object()};
        std::string reference_material{};    
        
        pMtlParseFunction add_reference_mat
        {[&](const auto& args){
            reference_material = args[0];
            jsonData[reference_material] = json::object();
        }};

        pMtlParseFunction add_float_value
        {[&](const auto& args){
            auto ss = std::istringstream{args[1]};
            float f;
            ss >> f;
            jsonData[reference_material][args[0]] = f;
        }};

        pMtlParseFunction add_int_value
        {[&](const auto& args){
            auto ss = std::istringstream{args[1]};
            unsigned int ui;
            ss >> ui;
            jsonData[reference_material][args[0]] = ui;
        }};

        pMtlParseFunction add_string_value
        {[&](const auto& args){
            jsonData[reference_material][args[0]] = args[1];
        }};
        
        pMtlParseFunction add_float_vector_value
        {[&](const auto& args){
            auto vsVectorToParse = std::vector<std::string>(args.begin() + 1, args.end());
            auto vfVectorToParse = std::vector<float>{};
            Wolf::VectorUtils::pushvectorf(vfVectorToParse, vsVectorToParse, 3);
            jsonData[reference_material][args[0]]{
                vfVectorToParse[0], 
                vfVectorToParse[1], 
                vfVectorToParse[2]};

        }};
        
        std::function<void()>
        print_model
        {[&](){
            std::cout << std::setw(4) << jsonData << std::endl;
        }};
        std::map<std::string, pMtlParseFunction> linetype_function{
            std::make_pair("newmtl", add_reference_mat),
            std::make_pair("Ns", add_float_value),
            std::make_pair("Ka", add_float_vector_value),
            std::make_pair("Kd", add_float_vector_value),
            std::make_pair("Ks", add_float_vector_value),
            std::make_pair("Ke", add_float_vector_value),
            std::make_pair("Ni", add_float_value),
            std::make_pair("d",  add_float_value),
            std::make_pair("illum", add_int_value),
            std::make_pair("map_Kd", add_string_value)            
        };
        auto LineIsIrrelevant = [&](auto& command_line_splitted, auto& command_line_splitted){
            if (command_line.empty()) return true;
            command_line_splitted = Wolf::StringUtils::split(line,' ');
            return linetype_function.find(command_line_splitted[0]) == linetype_function.end();
        }

    }rawmaterial;

    //Sweep file
    for (auto&line:file.lines){
        
        std::vector<std::string>commandStringVector{};
        if (LineIsIrrelevant(line, commandStringVector)) continue;
        rawmaterial.linetype_function[commandStringVector[0]](commandStringVector);
    
    }
    //Return
    return rawmaterial.jsonData;
}

std::tuple<const json, const std::vector<float>> Wolf::ObjParser::Serialize(const Wolf::File& file){

    enum wavefrontstate {
        none, mtllib, o, v, vt, vn, usemtl, s, f
    };
    
    using pOBJParseFunction = std::function<void(const std::vector<std::string>&)>; 
    struct {  
        std::tuple<const json&, const std::vector<float>&>   
        json jsonData{
            {"Geometry", json::object()},
            {"Material", json::object()}
        };
        std::string modelname{};
        std::string matlibfilename{};    
        std::vector<float> vertices{};
        std::vector<float> texcoord{};
        std::vector<float> vnormals{};
        std::vector<float> vfVBOData{};
        /*
         * Let's say we have a single quad triangulated mesh (2 triangles)  . So f might see like this:
         * f 0/0/0 1/2/2 2/1/1
         * f 1/2/2 3/3/3 2/1/1 
         * 
         * See the 4 VTNs? 0/0/0 1/2/2 2/1/1 and 3/3/3.
         * 
         * The following dicitionary would be: 
         * {
         *  "0/0/0" : 0,
         *  "1/2/2" : 1,
         *  "2/1/1" : 2,
         *  "3/3/3" : 3
         * }
         * 
         * At the end what we want to have as an EBO for opengl is two triangles described by index enumeration. 
         * Using the dictionary this triangles would be described as:
         * [0, 1, 2] ==> triangle 1
         * [2, 3, 1] ==> triangle 2.
         * 
         * Weell that's the idea of this registry to map OBJ "v/t/n" into OpenGl EBO index.
        */
        std::map<std::string, unsigned int> triangleVTNIndexRegistry{}; 
        
        pOBJParseFunction add_matlibfilename
        {[&](const auto& args){
            matlibfilename = args[1];
        }};

        pOBJParseFunction add_modelname
        {[&](const auto& args){
            modelname = args[1];
            jsonData["Geometry"][modelname] = json{
                {"mtllib", matlibfilename},
                {"meshes", json::array()}};

            auto matFile = Wolf::File(file.FolderPath(), args[1]);
            jsonData["Materials"][matlibfilename] = MtlParser(matFile);
        }};
        
        pOBJParseFunction add_reference_mat
        {[&](const std::string& args){
            auto& jmeshes = jsonData["Geometry"][modelname]["meshes"];
            auto  jmesh = json{
                {"reference_mat", args[1]},
                {"indexes_array", json::array()}
            };
            jmeshes.push_back(jmesh);
        }};
        
        std::function<void(const std::string &)> UpdateVBOData
        {[&](auto &sTriangleVTNKey){
            const auto arrTriangleIndices = GenerateVTNArray(sTriangleVTNKey);
            vfVBO.push_back(vertices[arrTriangleIndices[0] * 3 + 0]);
            vfVBO.push_back(vertices[arrTriangleIndices[0] * 3 + 1]);
            vfVBO.push_back(vertices[arrTriangleIndices[0] * 3 + 2]);
            vfVBO.push_back(texcoord[arrTriangleIndices[1] * 2 + 0]);
            vfVBO.push_back(texcoord[arrTriangleIndices[1] * 2 + 1]);
            vfVBO.push_back(vnormals[arrTriangleIndices[2] * 3 + 0]);
            vfVBO.push_back(vnormals[arrTriangleIndices[2] * 3 + 1]);
            vfVBO.push_back(vnormals[arrTriangleIndices[2] * 3 + 2]);    
        }};
 
        pOBJParseFunction add_triangle_indexes
        {[&](const auto& args){
            
            //Get Reference of our array.
            auto& indexes_array = jsonData["Geometry"][modelname]["meshes"][jsonData["Geometry"][modelname]["meshes"].size() - 1]["indexes_array"];
            auto& jtriangle_vertices_EBO_array = json::array();

            //Parse command tokens.
            auto vsTriangleVTNKeys = std::vector<std::string>(args.begin() + 1, args.end());
            for (auto& triangleVTNKey : vsTriangleVTNKeys){
                
                //Check if VTN is already registered in the VTN => EBO map.
                auto& triangleVTNIndexRegistry = triangleVTNIndexRegistry;
                auto triangleVTNKeyIsNotRegistered = triangleVTNIndexResgistry.find(triangleVTNKey) == triangleVTNIndexRegistry.end();
                
                //If not registered, register it.
                if (triangleVTNKeyIsNotRegistered) triangleVTNIndexRegistry[triangleVTNKey] = triangleVTNIndexRegistry.size();
                
                //Use register to add index to EBO array.
                jtriangle_vertices_EBO_array.push_back(triangleVTNIndexRegistry[triangleVTNKey]);

                //Update VBO Data using pData vectors (which resemble more the OBJ organizes vertices textures and normals.)
                UpdateVBOData(triangleVTNKey);

            }
            //Update array.
            indexes_array.push_back(jtriangle_vertices_EBO_array);
                
        }};
        
        pOBJParseFunction add_vector
        {[&](auto& args){
            auto vsVector = std::vector<std::string>(args.begin() + 1 args.end());
            if (args[0] == "v") Wolf::VectorUtils::pushvectorf(vertices, vsVector, 3);
            else if (args[0] == "vn") Wolf::VectorUtils::pushvectorf(vnormals, vsVector, 3);
            else if (args[0] == "vt") Wolf::VectorUtils::pushvectorf(texcoord, vsVector, 2);
        }};
        std::map<std::string, pOBJParseFunction> linetype_function{
            std::make_pair("mtllib", add_matlibfilename),
            std::make_pair("o", add_modelname),
            std::make_pair("v", add_vector),
            std::make_pair("vt", add_vector),
            std::make_pair("vn", add_vector),
            std::make_pair("usemtl", add_reference_mat),
            std::make_pair("f", add_triangle_indexes)
        };
        std::function<void()>
        print_model
        {[&](){
            std::cout << std::setw(4) << jsonData << std::endl;
        }};
        auto LineIsIrrelevant = [&](auto& command_line, auto& command_line_splitted){
            if (command_line.empty()) return true;
            auto command_line_splitted = Wolf::StringUtils::split(command_line,' ');
            return linetype_function.find(command_line_splitted[0]) == linetype_function.end();
        }
    }rawmodel;

    for (auto&line:file.lines){
        
        std::vector<std::string>commandStringVector{};
        if (LineIsIrrelevant(line, commandStringVector)) continue;
        rawmaterial.linetype_function[commandStringVector[0]](commandStringVector);

        
    }
    std::make_tuple(rawmodel.jsonData, rawmodel.vfVBOData);
}





