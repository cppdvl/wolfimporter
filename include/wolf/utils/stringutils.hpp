#ifndef __WOLF_STRINGUTILS_H__
#define __WOLF_STRINGUTILS_H__
#include <map>
#include <tuple>
#include <vector>
#include <sstream>

namespace Wolf::Utils::StringUtils {

		std::vector<std::string> split(const std::string& s, const std::string& delim);
		std::string join(std::vector<std::string> vs, const std::string s, int firstindex = 0, int lastindex = 0);


		std::tuple<bool,int> bi_isint(const std::string& str);
        std::tuple<bool, unsigned int> bui_isint(const std::string&);

}
namespace Wolf{
    namespace StringUtils {
		
        
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