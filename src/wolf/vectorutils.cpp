
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

        void pushvectorf(std::vector<float>& v, std::vector<std::string>&vs, int n){

            auto ss = std::istringstream{vs[0]};
            float f; 
            ss >> f;
            v.push_back(f);
            if (--n > 0){
                auto nextvs = std::vector<std::string>(vs.begin() + 1, vs.end());
                pushvectorf(v, nextvs, n);
            }

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