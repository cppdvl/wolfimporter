#ifndef __WOLF_WAVEFRONTUTILS_H__
#define __WOLF_WAVEFRONTUTILS_H__

#include <string>
#include <vector>
#include <sstream>

namespace Wolf{
    namespace WavefrontUtils {
		void pushfaceindexes(std::vector<unsigned int>&v, std::vector<unsigned int>&t, std::vector<unsigned int>&n, std::string s);
		
	}
}

#endif