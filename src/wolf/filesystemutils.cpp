#include <string>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
namespace Wolf {
    namespace FileSystemUtils {

        std::ifstream open(const std::string& rrelpath){
            auto relpath = fs::path{rrelpath};
	        auto abspath = fs::absolute(relpath);
	        std::ifstream ifp(abspath, std::ios::in);
            return ifp;
        }
        void close(std::ifstream& rifp){
            rifp.close();
        }
    }
}