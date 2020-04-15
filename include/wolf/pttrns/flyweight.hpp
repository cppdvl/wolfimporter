#ifndef __WOLF_FLYWEIGHT_H__
#define __WOLF_FLYWEIGHT_H__

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

namespace Wolf {
    namespace FlyWeight {
        template <typename C, typename U> //Common, Unique
        class FW : public std::vector<U> {

        public:
            C commonData;
            explicit FW() = default;

            explicit FW(const C& c){
                this->commonData = c;
            }
        };
    }
}

#endif //__WOLF_FLYWEIGHT_H__
