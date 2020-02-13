#ifndef __WOLF_VECTORUTILS_H__
#define __WOLF_VECTORUTILS_H__

#include <string>
#include <vector>

namespace Wolf {
    namespace VectorUtils {
		void pushvectorf(std::vector<float>& v, std::istringstream&ss, int n);
		void pushvectorf(std::vector<float>& v, std::string&s, int n);
	}
}

#endif
