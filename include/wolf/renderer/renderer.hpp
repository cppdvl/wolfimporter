#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <wolf/pttrns/flyweight.hpp>

namespace Wolf {

    namespace Renderer {

        template <typename I> 
        class FWVAO_T : public Wolf::FlyWeight::FW<unsigned int, I>{
        public:
            FWVAO_T(const unsigned int& uiVao){
                this->commonData = uiVao;
                
            };

        };
        template <typename S, typename I> 
        class FWSHDR__FWVAO_T : public Wolf::FlyWeight::FW<S, FWVAO_T<I>>{
        public:

        };
        template <typename S, typename I>
        
        class Primitives {
        protected:
            FWSHDR__FWVAO_T<S,I> _submittedPrimitives;
        public:
            void SetShader(S const& shader){
                _submittedPrimitives.commonData = shader;
            }
            void PushInsance(I const& instance){
                _submittedPrimitives.push_back(instance);
            }

        };    

    }
 
}
#endif //__RENDERER_H__