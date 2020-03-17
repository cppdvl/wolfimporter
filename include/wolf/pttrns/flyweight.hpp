#include <iostream>
#include <vector>
#include <glm/glm.hpp>

namespace Wolf {
    namespace FlyWeight {
        template <typename C, typename U> //Common, Unique
        class Data{
        protected:
            C common_object;
            std::vector<U> unique_objects;
        public:
            explicit Data(){}
            explicit Data(const C& commonObjectID){
                common_object = commonObjectID;
            }
            explicit Data(const C& commonObjectID, const std::vector<U>& uniqueObjectIDVector){
                common_object = commonObjectID;
                std::for_each(uniqueObjectIDVector.begin(), uniqueObjectIDVector.end(), [&](auto& uniqueObjectID){
                    unique_objects.push_back(uniqueObjectID);
                });
            }
            virtual U& PushElement(U&&u){
                unique_objects.emplace_back(std::move(u));
                return unique_objects.back();
            }
            virtual U& CreateElementAndPush(){
                return PushElement(U{});
            }
            U* GetDataArray(){
                if (unique_objects.empty()) return nullptr;
                return unique_objects.data();
            }
            virtual ~Data(){}

        };

        class CommonElements{
            protected:
            unsigned int uiShaderProgram{0};
            unsigned int uiVao{0};

            public:
            CommonElements() = default;
            const unsigned int& GetShaderProgram() const {return uiShaderProgram;}
            const unsigned int& GetVao() const {return uiVao;}
            friend class Renderer; 
        };
        class EntityUniqueElements{
            
            protected:
            std::vector<glm::mat4> tMatVector{};

            public:
            std::vector<glm::mat4>& GetMatVector(){ return tMatVector;}
            friend class Renderer; 

        };
        
        class Renderer {
            protected:
            /*!
            @brief Elements that are unique per each entity.
            */
            EntityUniqueElements eue{};
            
            public:
            /*!
            @brief Common Elements 
            */
            CommonElements ce{};
            explicit Renderer(const unsigned int& uiShaderProgram, const unsigned int& uiVao){
                ce.uiShaderProgram = uiShaderProgram;
                ce.uiVao = uiVao;
            }
            virtual glm::mat4* PushTMat(glm::mat4 && tMat){
                auto& rMatVector = eue.GetMatVector();
                rMatVector.emplace_back(std::move(tMat));
                auto sz = rMatVector.size() - 1;
                return rMatVector.data() + sz;
            }
            virtual void RenderElements() = 0;     
            
            
        };
    }
    
}
