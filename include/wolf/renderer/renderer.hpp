#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <wolf/pttrns/flyweight.hpp>

namespace Wolf {

    namespace Renderer {

        /**
         * @brief      This class describes a fwvao t. Common part is vector of VAOs (which is the archetype of a 3D Mesh Object),
         *             and a list of Matrices, each one owned by an entitty.
         *
         * @tparam     I The type of an object with the purpose of describe the state of a particular object.
         */
        template <typename I> 
        class FWVAO_T : public Wolf::FlyWeight::FW<unsigned int, I>{
        public:
            FWVAO_T() = default;
            explicit FWVAO_T(const unsigned int& uiVao) : Wolf::FlyWeight::FW<unsigned int, I>(uiVao){

            }
            explicit FWVAO_T(const std::vector<unsigned int>& vuiVao) : Wolf::FlyWeight::FW<unsigned int, I>(vuiVao){

            };


            virtual ~FWVAO_T(){}
        };
        template <typename S, typename I> 
        class FWSHDR__FWVAO_T : public Wolf::FlyWeight::FW<S, FWVAO_T<I>>{
        public:
            explicit FWSHDR__FWVAO_T() = default;
            explicit FWSHDR__FWVAO_T(const S& s) : Wolf::FlyWeight::FW<S, FWVAO_T<I>>(s){}
        };
        template <typename S, typename I>
        
        class ShaderDomain : public FWSHDR__FWVAO_T<S,I> {
        public:
            ShaderDomain() = default;
            ShaderDomain(const S& s) : FWSHDR__FWVAO_T<S,I>(s){}
            void SetShader(S const& shader){
                this->commonData.push_back(shader);
            }


        };    

    }
 
}
#endif //__RENDERER_H__