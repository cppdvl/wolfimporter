#ifndef WOLF_FILE
#define WOLF_FILE

#include <array>

#include <string>
#include <vector>

#include <fstream>

#include <iostream>


#include "wolf/utils/filesystemutils.hpp"

namespace Wolf {
    class File {
        bool exists{ false };
        std::string folder_path{};
        std::string absolute_path{};
        std::string filename{};

        void _init(const std::filesystem::path&);
        void _open(const std::filesystem::path&);
        void _close();
    public:
        File(const std::string& path, const std::string& filename);
        File(const std::string& rrelpath);
        File(const File&) = default;
        std::vector<std::string>lines{};
        void DumpFile();
        const bool& Valid() const {
            return exists;
        }
        const std::string& FolderPathRef() const {
            return folder_path;
        }
        std::string FolderPath() const {
            return folder_path;
        }
        const std::string& AbsolutePathRef() const {
            return absolute_path;
        }
        std::string AbsolutePath() const {
            return absolute_path;
        }
    };
}
#endif //WOLF_FILE