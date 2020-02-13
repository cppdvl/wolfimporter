#include <map>
#include <vector>
#include <sstream>

namespace Wolf{
    namespace StringUtils {
		
		std::vector<std::string> split(std::string& s, char delim){
			
			auto ss = std::istringstream{s};
			auto ssplit = std::vector<std::string>{};
			auto stringtoken = std::string{};
			while (std::getline(ss, stringtoken, delim)) ssplit.push_back(stringtoken);
			return ssplit;
		
		}
		std::string join(std::vector<std::string> vs, char c, unsigned int firstindex){
			std::string acc{};
			
			for (auto &s : vs){
				if (firstindex) {
					firstindex--;
					continue;
				}
				acc += s;
				acc += std::string{c};
			}
			return acc;
		}
        
	}
}