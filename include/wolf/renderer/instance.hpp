#ifndef __WOLF_RENDERER_OBJECTRENDERINGDATA__
#define __WOLF_RENDERER_OBJECTRENDERINGDATA__

namespace Wolf {
    namespace Renderer {
        template <typename M>
        class Instance {
        public:
            Instance( ) = default;
            Instance( const Instance& other) = default;
            Instance( Instance&& other) = default;
            Instance& operator=(const Instance& other){
                tMatrix = other.tMatrix;
                return *this;
            }
            /*struct {

                float textureFactor {1.0f};
                int colselector_x{5};
                int colselector_y{3};
                float sprite_texture_width{0.166666666};
                float sprite_texture_height{0.0526315};

            } shaderConfigurationInfo;*/
            virtual ~Instance(){

            }
            /**
             * A matrix describing the orientation and translation of an object.
             */
            M tMatrix{};

        };

    }
}

#endif //__WOLF_RENDERER_OBJECTRENDERINGDATA__