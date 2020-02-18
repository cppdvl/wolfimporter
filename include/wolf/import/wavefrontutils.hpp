#ifndef __WOLF_WAVEFRONTUTILS_H__
#define __WOLF_WAVEFRONTUTILS_H__

#include <string>
#include <vector>
#include <sstream>
#include "wolf/stringutils.hpp"

namespace Wolf{
    namespace WavefrontUtils {
		void pushfaceindexes(std::vector<unsigned int>&v, std::vector<unsigned int>&t, std::vector<unsigned int>&n, std::string s){
			
			auto s_space = Wolf::StringUtils::split(s, ' ');
			for (auto it = s_space.begin(); it != s_space.end(); ++it){
				auto vs_indexes = Wolf::StringUtils::split(*it, '/');
				unsigned int ui_parsed{};
				std::stringstream{vs_indexes[0]} >> ui_parsed;
				v.push_back(--ui_parsed);
				std::stringstream{vs_indexes[1]} >> ui_parsed;
				t.push_back(--ui_parsed);
				std::stringstream{vs_indexes[2]} >> ui_parsed;
				n.push_back(--ui_parsed);
			}
		}
	}
}

#endif