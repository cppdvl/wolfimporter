#ifndef __WOLF_FILE__
#define __WOLF_FILE__

#include <string>
#include <vector>


namespace Wolf {
    namespace _3DFormats {
        class _File {
		public:
            _File(const std::string& rrelpath);
            std::vector<std::string>lines{};
            void DumpFile();
        };
               
    }
}
#endif