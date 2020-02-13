#include <string>
#include <vector>
#include <sstream>

namespace Wolf {
    namespace VectorUtils {
		void pushvectorf(std::vector<float>& v, std::istringstream&ss, int n){
			float f;
			ss >> f;
			v.push_back(f);
			if (--n > 0) pushvectorf(v, ss, n);
		}
		void pushvectorf(std::vector<float>& v, std::string&s, int n){
			
			auto ss = std::istringstream{s};
			float f;
			ss >> f;
			v.push_back(f);
			if (--n > 0) pushvectorf(v, ss, n);
			
		}
        
	}
}