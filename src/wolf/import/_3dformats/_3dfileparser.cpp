#include <map>
#include <iomanip>
#include <iostream>

#include "wolf/import/_3dformats/_3dfileparser.hpp"

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


