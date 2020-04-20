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
        class FWVAO_T : public Wolf::FlyWeight::FW<unsigned long, I>{
        public:
            FWVAO_T() = default;
            explicit FWVAO_T(const unsigned int& uiVao, const unsigned int& uiNVtx) : Wolf::FlyWeight::FW<unsigned long, I>((uiNVtx << 32) + (uiVao & 0xFFFFFFFF)){

            }
            explicit FWVAO_T(const std::vector<unsigned long>& v_uiNVtxuiVao) : Wolf::FlyWeight::FW<unsigned long, I>(v_uiNVtxuiVao){

            };


            virtual ~FWVAO_T(){}
        };

        template <typename I>
        class VAODomain : public FWVAO_T<I>{
        public:
            explicit VAODomain() = default;
            explicit VAODomain(const std::vector<unsigned long>& vuiVao) : FWVAO_T<I>(vuiVao){}

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

        template <typename C, typename S, typename I>
        class FWC___FWSDHR__FWVAO_T : public Wolf::FlyWeight::FW<C, FWSHDR__FWVAO_T<S,I>>{
            explicit FWC___FWSDHR__FWVAO_T() = default;
            explicit FWC___FWSDHR__FWVAO_T(const C& c) : Wolf::FlyWeight::FW<C, FWSHDR__FWVAO_T<S, I>>(c){}
        };

        template <typename C, typename S, typename I>
        class CameraDomain : public FWC___FWSDHR__FWVAO_T<C, S, I>{
            CameraDomain() = default;
            CameraDomain(const C& c) : FWC___FWSDHR__FWVAO_T<C, S, I>(c){}
            void SetCamera(C const& camera){
                this->commonData.push_back(camera);
            }

        };

    }
 
}
#endif //__RENDERER_H__