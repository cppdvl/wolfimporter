#ifndef WOLF_RENDERER_VAODATA_H
#define WOLF_RENDERER_VAODATA_H


namespace Wolf {
    namespace Renderer{
        /**
         * @brief      This is the a Common VAO might be used within a Component or along with it.
         */
        class GeometryData{

        public:
            union {
                std::uint64_t data_raw;
                struct {
                    std::uint32_t vaoHnd;   //Vao Handle
                    std::uint32_t vtxCnt;   //Vertex Count
                }data;
            }u;
            static std::vector<ModelData> addVaoVtxCount(
                std::vector<std::uint32_t> vaoHandl,
                std::vector<std::uint32_t> vtxCount){

                auto vModelData = std::vector<Wolf::Renderer::ModelData>{}; 
                if (vaoHandl.size() != vtxCount.size()) return vModelData;

                auto sz = vaoHandl.size();
                for(auto index = 0; index < sz; ++index){
                    
                    vModelData[index].u.data.vaoHandl = vaoHnd[index];
                    vModelData[index].u.data.vtxCount = vtxCnt[index]; 
                }
            }
        };
    }
}


#endif //WOLF_