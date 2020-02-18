#include <array>
#include <fstream>
#include <iostream>
#include "wolf/filesystemutils.hpp"
#include "wolf/import/_3dformats/file.hpp"

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