#ifndef __WOLF_VECTORUTILS_H__
#define __WOLF_VECTORUTILS_H__

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Wolf {
    namespace VectorUtils {
		void pushvectorf(std::vector<float>& v, std::istringstream&ss, int n);
		void pushvectorf(std::vector<float>& v, std::string&s, int n);
		void pushvectorf(glm::vec3& v, std::string&s);
	}
}

#endif
