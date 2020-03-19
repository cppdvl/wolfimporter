#include <array>
#include <fstream>
#include <iostream>
#include "wolf/filesystemutils.hpp"
#include "wolf/import/_3dformats/file.hpp"


#include <filesystem>
namespace fs = std::filesystem;

bool SanityCheck(const fs::path& abspath) {
	return fs::exists(abspath);
}
void Wolf::_3DFormats::_File::_init(const fs::path& relative_path) {

	auto foldertmppath = relative_path;
	filename = foldertmppath.filename().string();
	foldertmppath.remove_filename();
	folder_path = foldertmppath.string();
	
	absolute_path = fs::absolute(relative_path).string();
	
	exists = SanityCheck(absolute_path);

}
void Wolf::_3DFormats::_File::_open(const fs::path& relative_path){

	_init(relative_path);
	if (!exists) return;
	std::ifstream ifp(relative_path, std::ios::in);
	while (!ifp.eof()) {
		std::array<char, 1024> a{};
		ifp.getline(&a[0], 1024);
		auto line = std::string{ a.data() };
		lines.push_back(line);
	}
	ifp.close();
}
Wolf::_3DFormats::_File::_File(const std::string& rpath, const std::string& rfilename) {
	
	auto relative_path = fs::path{ rpath } / fs::path{ rfilename };
	_open(relative_path);
	
}
Wolf::_3DFormats::_File::_File(const std::string& rrelpath){
	
	auto relative_path = fs::path{ rrelpath };
	_open(relative_path);
	
}

void Wolf::_3DFormats::_File::DumpFile(){
	
	for(auto&line:lines){
		std::cout << line << std::endl;
	}
}