#ifndef __WOLF_FILESYSTEMUTILS_H__
#define __WOLF_FILESYSTEMUTILS_H__
#include <string>
#include <fstream>
#include <filesystem>
namespace Wolf {
    namespace FileSystemUtils {

        std::ifstream open(const std::string& rrelpath);
        void close(std::ifstream& rifp);
        std::string filename(std::string& s) { return std::filesystem::absolute(s).string(); }
    }
}

#endif
