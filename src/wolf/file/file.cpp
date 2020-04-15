#include <array>
#include <fstream>
#include <iostream>
#include "wolf/utils/filesystemutils.hpp"
#include "wolf/file/file.hpp"


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
    for(auto a = std::vector<char>{}; !ifp.eof();){
        
        //No Void Lines
        auto endline = ifp.peek() == '\n' ? true : false;
        auto voidline = a.empty();
        if ( endline ){
            if ( !voidline ){
                line.push_back(a);
                a.clear();
            } else ifp.get();
        } else {
            a.push_back(ifp.get())
        }
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