
#include <string>
#include <vector>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
        void pushvectorf(glm::vec3& v, std::string&s){

            auto ss = std::istringstream{s};
            float x, y, z;
            ss >> x;
            ss >> y;
            ss >> z;
            v = glm::vec3(x, y, z);

        }
    }
}