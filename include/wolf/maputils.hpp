#ifndef __WOLF_MAPUTILS_H__
#define __WOLF_MAPUTILS_H__
#include <map>
#include <vector>

namespace Wolf{

    namespace MapUtils {
		
		template <typename K, typename V>
		std::vector<K> keys(const std::map<K,V>&m){
			std::vector<K>ks{}; 
			std::for_each(m.begin(), m.end(), [&](auto p){
				ks.push_back(p.first);
			});
			return ks;
		}

	}
}


#endif