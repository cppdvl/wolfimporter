#ifndef WOLF_FILE
#define WOLF_FILE
    
namespace Wolf {
    class _File {
        bool exists{ false };
        std::string folder_path{};
        std::string absolute_path{};
        std::string filename{};

        void _init(const std::filesystem::path&);
        void _open(const std::filesystem::path&);
        void _close();
    public:
        _File(const std::string& path, const std::string& filename);
        _File(const std::string& rrelpath);
        _File(const _File&) = default;
        std::vector<std::string>lines{};
        void DumpFile();
        const bool& Valid() const {
            return exists;
        }
        const std::string& FolderPath() const {
            return folder_path;
        }
        const std::string& AbsolutePath() const {
            return absolute_path;
        }
    };
}
#endif //WOLF_FILE