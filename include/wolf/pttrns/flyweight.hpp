#ifndef __WOLF_FLYWEIGHT_H__
#define __WOLF_FLYWEIGHT_H__

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

namespace Wolf {
    namespace FlyWeight {
        template <typename C, typename U> //Common, Unique
        class FW : public std::vector<U> {
        protected:
            C* ptrEnd{0x00};

        public:
            std::vector<C> commonData;
            explicit FW() = default;
            explicit FW(const C& c){
                this->commonData.push_back(c);
            }
            explicit FW(const std::vector<C>& vCommonData){
                this->commonData = vCommonData;
            }
            //Capacity
            /*!
             * @brief Get The Number of Common Elements
             * @return The Number of Common Elements
             */
            inline auto CommonDataSize() const{
                return this->commonData.size();
            }

            //Raw Iteration : This are unsafe but quick iterations.
            /*!
             * @brief Get a Raw Pointer to the first element in the common data list.
             * @return
             */
            inline auto CommonDataPtr() {
                auto ptrStart = commonData.data();
                auto sz = commonData.size();
                this->ptrEnd = ptrStart + sz;
                return this->commonData.data();
            }
            /*!
             * @brief Get the first out of bounds address in the common Data List. The effect of this function is valid only when CommonDataPtr has been called.
             * @return A Pointer to the first address out of the commonData vector boundaries.
             */
            inline auto CommonDataEnd() const {
                auto ptr = this->commonData.data();
                return ptr + this->CommonDataSize();
            }
            /*!
             * @brief Move the Pointer to the next element
             * @param ptrNow A iteration pointer to move
             * @return if the ptr now is out of bound the function will return false, and the pointer will be nullified.
             */
            inline bool CommonStepPtr(unsigned int*& ptrNow) const{
                ptrNow++;
                auto ret = (ptrNow != this->ptrEnd);
                if (!ret) ptrNow = nullptr;
                return ret;
            }

        };
        
    }


}

#endif //__WOLF_FLYWEIGHT_H__
