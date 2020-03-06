#include <map>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "wolf/import/_3dformats/_3dfileparser.hpp"



std::map<std::string, std::vector<float>> Wolf::_3DFormats::_3DFileParser::DumpCodeVectorMap(std::string objectname){

    auto exitWithMessage = [&](const std::string& message, const std::string& elem){
        std::cout << __func__ << " : " << message << elem << std::endl;
        std::exit(-1);
    }; auto objectfound = objectname__shadername_vtn.find(objectname) != objectname__shadername_vtn.end();
    if (!objectfound) exitWithMessage("Object not found: ", objectname);
	return objectname__shadername_vtn[objectname];
}
std::vector<float> Wolf::_3DFormats::_3DFileParser::DumpCodeVector(std::string objectname, std::string shadername){

    auto exitWithMessage = [&](const std::string& message, const std::string& elem){
        std::cout << __func__ << " : " << message << elem << std::endl;
        std::exit(-1);
    };auto object = DumpCodeVectorMap(objectname);
    auto shaderfound = object.find(shadername) != object.end();
    if (!shaderfound) exitWithMessage("Shader not found: ", shadername);
    return object[shadername];
	
}


void Wolf::_3DFormats::_3DFileParser::DumpCode(std::string nameoftheobject, std::string nameoftheshader){


    auto memaddress = DumpCodeVector(nameoftheobject, nameoftheshader).data();

    std::cout << nameoftheobject << "|" << nameoftheshader << " 0x" << std::hex << memaddress << std::endl;
	std::cout << "float fdata[] = { ";
	int index = 0;
	int size = objectname__shadername_vtn[nameoftheobject][nameoftheshader].size();
	for (auto& fvalue : objectname__shadername_vtn[nameoftheobject][nameoftheshader]) {
		if (index % 8 == 0) std::cout << "\n\t";
		std::cout << std::fixed << std::setw( 6 ) << std::setprecision( 6 ) << fvalue; 
		if (index + 1 < size) std::cout << ", ";
		else std::cout << "\n};" << std::endl;
		index++;
	}
}

Wolf::_3DFormats::_3DMaterial Wolf::_3DFormats::_3DFileParser::DumpMaterialInformation(std::string libraryname, std::string materialname){

    auto exitWithMessage = [&](const std::string& message, const std::string& elem){
        std::cout << __func__ << " : " << message << elem << std::endl;
        std::exit(-1);
    };
    auto libraryfound = matlibraryname__matname_mat.find(libraryname) != matlibraryname__matname_mat.end();
    if (!libraryfound) exitWithMessage("Library not found: ", libraryname);
    auto &library = matlibraryname__matname_mat[libraryname];
    auto materialfound = library.find(materialname) != library.end();
    if (!materialfound) exitWithMessage("Materialname not found: ", materialname);
    return library[materialname];
    
}
