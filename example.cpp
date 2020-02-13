#include <map>
#include <array>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include "include/wolf/filesystemutils.hpp"
#include "include/wolf/vectorutils.hpp"
#include "include/wolf/stringutils.hpp"
#include "include/wolf/maputils.hpp"

namespace fs = std::filesystem;
namespace Wolf {

    
	
	namespace WavefrontUtils {
		void pushfaceindexes(std::vector<unsigned int>&v, std::vector<unsigned int>&t, std::vector<unsigned int>&n, std::string s){
			
			auto s_space = Wolf::StringUtils::split(s, ' ');
			for (auto it = s_space.begin(); it != s_space.end(); ++it){
				auto vs_indexes = Wolf::StringUtils::split(*it, '/');
				unsigned int ui_parsed{};
				std::stringstream{vs_indexes[0]} >> --ui_parsed;
				v.push_back(--ui_parsed);
				std::stringstream{vs_indexes[1]} >> --ui_parsed;
				t.push_back(--ui_parsed);
				std::stringstream{vs_indexes[2]} >> --ui_parsed;
				n.push_back(--ui_parsed);
			}
		}
	}
	namespace _3DFormats {
        class _File {
            public:
                _File(const std::string& rrelpath);
                std::vector<std::string>lines{};
                void DumpFile();
        };
		class _3DMaterial {
		
        	public:
				std::vector<float> ka{}, ks{}, kd{}, ke{}; //Ambient, Specularity, Diffuse, Emissive 
				float opacity;	
                float specularExponent; //Ns
                float opticalDensity; //Ni
		
        };
        class _3DMaterialLibraryFile : public _File {
            public:
                _3DMaterialLibraryFile(const std::string& rrelpath) : _File(rrelpath){
					
				}
                std::map<std::string, _3DMaterial> materialname_material{};
                virtual bool Serialize() = 0;
				
        };
        class MTLFileParser : public _3DMaterialLibraryFile {
        
            public:
				MTLFileParser(const std::string& rrelpath) : _3DMaterialLibraryFile(rrelpath){}
                bool Serialize() override;

        };
		class _3DFileParser : public _File {
			public:
				_3DFileParser(const std::string& rrelpath):_File(rrelpath){}
				
				
				//Print Code for Object with a particular shader
				void DumpCode(std::string, std::string);
				
				//Get Vertex Buffer Object with Shader.
				std::vector<float> DumpCodeVector(std::string, std::string);
				
				//Get Vertex Buffer Object Map. 
				std::map<std::string, std::vector<float>> DumpCodeVectorMap(std::string);
				
				//Parse the format.
				virtual bool Serialize() = 0;
				
			protected:
				std::map<std::string, std::map<std::string, std::vector<float>>> objectname__shadername_vtn{};
				std::map<std::string, std::map<std::string, _3DMaterial>> matlibraryname__matname_mat{};		
		};
		
		class OBJFileParser : public _3DFileParser {

			public:
				OBJFileParser(const std::string& rrelpath) : _3DFileParser(rrelpath){};
				bool Serialize() override;
				
		};
		
	}
}
std::map<std::string, std::vector<float>> Wolf::_3DFormats::_3DFileParser::DumpCodeVectorMap(std::string objectname){
	
	auto objectnamefound = objectname__shadername_vtn.find(objectname) != objectname__shadername_vtn.end();
	if (!objectnamefound) return std::map<std::string, std::vector<float>>{};
	
	return objectname__shadername_vtn[objectname];
}
std::vector<float> Wolf::_3DFormats::_3DFileParser::DumpCodeVector(std::string objectname, std::string shadername){
	
	auto objectnamefound = objectname__shadername_vtn.find(objectname) != objectname__shadername_vtn.end();
	if (!objectnamefound) return std::vector<float>{};
	auto shadernamefound = objectname__shadername_vtn[objectname].find(shadername) != objectname__shadername_vtn[objectname].end();
	if (!shadernamefound) return std::vector<float>{};
		
	return objectname__shadername_vtn[objectname][shadername];
	
}
Wolf::_3DFormats::_File::_File(const std::string& rrelpath){

    std::ifstream inputfilestream = Wolf::FileSystemUtils::open(rrelpath);
	while(!inputfilestream.eof()){
		std::array<char, 1024> a{};
		inputfilestream.getline(&a[0],1024);
		auto line = std::string{a.data()};
		lines.push_back(line);
	}
    Wolf::FileSystemUtils::close(inputfilestream); 

}

void Wolf::_3DFormats::_File::DumpFile(){
	
	for(auto&line:lines){
		std::cout << line << std::endl;
	}
}
void Wolf::_3DFormats::_3DFileParser::DumpCode(std::string nameoftheobject, std::string nameoftheshader){
	auto memaddress = (unsigned long long) objectname__shadername_vtn[nameoftheobject][nameoftheshader].data();
	std::cout << nameoftheobject << "|" << nameoftheshader << " 0x" << std::hex << memaddress << std::endl;
	std::cout << "float fdata[] = { ";
	int index = 0;
	int size = objectname__shadername_vtn[nameoftheobject][nameoftheshader].size();
	for (auto& fvalue : objectname__shadername_vtn[nameoftheobject][nameoftheshader]) {
		if (index % 8 == 0) std::cout << "\n\t";
		std::cout << std::fixed << std::setw( 6 ) << std::setprecision( 6 ) << fvalue; 
		if (index + 1 < size) std::cout << ",";
		else std::cout << "\n};" << std::endl;
		index++;
	}
}

bool Wolf::_3DFormats::MTLFileParser::Serialize() {

    enum wavefrontstate {
        none, newmtl, Ns, Ka, Kd, Ks, Ke, Ni, d, illum
    };
    auto state = none;
    std::string nameofthematerial{};
    std::string nameofthetexture{};
    std::map<std::string, wavefrontstate> linetype_state{
        std::make_pair("newmtrl", newmtl),
        std::make_pair("Ns", Ns),
        std::make_pair("Ka", Ka),
        std::make_pair("Kd", Kd),
        std::make_pair("Ks", Ks),
        std::make_pair("Ke", Ke),
        std::make_pair("Ni", Ni),
        std::make_pair("d", d),
        std::make_pair("illum", illum)
    };

    for (auto&line:lines){
        if (line.empty())continue;
        auto commandStringVector = Wolf::StringUtils::split(line, ' ');
        state = linetype_state[commandStringVector[0]];
        auto commandString = Wolf::StringUtils::join(commandStringVector, ' ', 1);
        if ( state == newmtl){
            nameofthematerial = commandStringVector[1];
            materialname_material[nameofthematerial] = _3DMaterial{};
            continue;
        } 
        auto& rMaterial = materialname_material[nameofthematerial];

        if (state == Ns){
            rMaterial.specularExponent = Wolf::StringUtils::parse<float>(commandStringVector[1]);
        } else if ( state == Ka){
            Wolf::VectorUtils::pushvectorf(rMaterial.ka, commandString, 3);
        } else if ( state == Kd){
            Wolf::VectorUtils::pushvectorf(rMaterial.kd, commandString, 3);
        } else if ( state == Ks){
            Wolf::VectorUtils::pushvectorf(rMaterial.ks, commandString, 3);
        } else if ( state == Ke){
            Wolf::VectorUtils::pushvectorf(rMaterial.ke, commandString, 3);
        } else if ( state == Ni){
            rMaterial.opticalDensity = Wolf::StringUtils::parse<float>(commandStringVector[1]);
        } else if ( state == d){
            rMaterial.opacity = Wolf::StringUtils::parse<float>(commandStringVector[1]);
        } else if ( state == illum){
            continue;
        }
    }
	return true;
}
bool Wolf::_3DFormats::OBJFileParser::Serialize()  {
	
	std::vector<float> vertices{};
	std::vector<float> texcoord{};
	std::vector<float> vnormals{};
	
	
	
	enum wavefrontstate {
		none, mtllib, o, v, vt, vn, usemtl, s, f
	};
	
	
	auto state = none;
	std::string nameofthegame{};
	std::string nameofthemateriallibrary{};
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
		state = linetype_state[commandStringVector[0]];
		auto commandString = Wolf::StringUtils::join(commandStringVector,' ', 1);
		
		if (state == mtllib) {
			
                
	        auto pMaterialFileParser = std::make_unique<MTLFileParser>(commandStringVector[1]);
            pMaterialFileParser->Serialize();
            
            matlibraryname__matname_mat[nameofthemateriallibrary] = pMaterialFileParser->materialname_material;

        }
		if (state == o)  {
			
			nameoftheobject = commandStringVector[1];
			objectname__shadername_vtn[nameoftheobject] = std::map<std::string, std::vector<float>>{};
			
		}
		if (state == usemtl){
			nameoftheshader = nameofthemateriallibrary + "/" + commandStringVector[1];
			objectname__shadername_vtn[nameoftheobject][nameoftheshader] = std::vector<float>{};
		}
		if (state == v)  
			Wolf::VectorUtils::pushvectorf(vertices, commandString, 3);
		if (state == vn) 
			Wolf::VectorUtils::pushvectorf(vnormals, commandString, 3);
		if (state == vt) 
			Wolf::VectorUtils::pushvectorf(texcoord, commandString, 2);
		if (state == f){
			
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
int main()
{
    Wolf::_3DFormats::OBJFileParser objdata("fuhrercube.obj");
    objdata.Serialize();
	objdata.DumpFile();
	objdata.DumpCode("Cube", "FuhrerSample.mtl/Blue");
	objdata.DumpCode("Cube.001", "FuhrerSample.mtl/FuhrerGlass");
	
	auto planeMap = objdata.DumpCodeVectorMap("Cube");
	auto planeMapKeys = Wolf::MapUtils::keys(planeMap);
	std::for_each(planeMapKeys.begin(), planeMapKeys.end(), [](auto&p){std::cout << p << std::endl;});
	
	return 0;
}