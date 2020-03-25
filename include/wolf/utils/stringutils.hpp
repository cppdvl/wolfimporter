#ifndef __WOLF_STRINGUTILS_H__
#define __WOLF_STRINGUTILS_H__
#include <map>
#include <vector>
#include <sstream>

namespace Wolf{
    namespace StringUtils {
		
		std::vector<std::string> split(std::string& s, char delim);
		std::string join(std::vector<std::string> vs, char c, unsigned int firstindex = 0);
        template <typename T>
        T parse(const std::string& s){
            T parsed;
            auto ss = std::istringstream{s};
            ss >> parsed;
            return parsed;
        }
	}
}
#endif