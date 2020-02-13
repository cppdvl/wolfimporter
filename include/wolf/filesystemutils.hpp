#ifndef __WOLF_FILESYSTEMUTILS_H__
#define __WOLF_FILESYSTEMUTILS_H__
#include <string>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
namespace Wolf {
    namespace FileSystemUtils {

        std::ifstream open(const std::string& rrelpath);
        void close(std::ifstream& rifp);
    
    }
}

#endif
