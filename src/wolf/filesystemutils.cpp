#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
namespace Wolf {
    namespace FileSystemUtils {

        std::ifstream open(std::string& rrelpath){
            
            auto relpath = fs::path{rrelpath};
	        relpath = fs::absolute(relpath);
            auto fileok = fs::exists(relpath);
            
            

	        std::ifstream ifp(relpath, std::ios::in);
            return ifp;
        }
        void close(std::ifstream& rifp){
            rifp.close();
        }
    }
}