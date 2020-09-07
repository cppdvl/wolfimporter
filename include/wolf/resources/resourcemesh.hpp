//
// Created by User on 7/26/2020.
//

#pragma once
#include <wolf/resources/resource.hpp>

namespace Wolf::Resources {

    class ResourceMeshData : public std::vector<float> {
    public:
        enum class BufferLayout{
            VNC,
            VCN,
            VN,
            VC,
            V
            //VTN,
            //VNT,
            //VT
        };
    private:
        BufferLayout mBufferLayout{BufferLayout::V};
        std::vector<unsigned int> mFaceIndices{};
        bool mHasFaces{false};
    public:

        explicit ResourceMeshData() = default;
        explicit ResourceMeshData(
                const std::vector<glm::vec3> &vertices,
                const std::vector<glm::vec3> &colors,
                const std::vector<glm::uvec3> &faces,
                ResourceMeshData::BufferLayout layout = ResourceMeshData::BufferLayout::V);

    };
    class ResourceMesh : public Wolf::Resources::Resource, public ResourceMeshData {

    public:
        /* Normals using face (CCW winding):
         *
         * face_ijk = [v[i], v[j], v[k]]
         * normal_ijk(face_ijk) = (v[j] - v[i]) X (v[k] - v[i])
         *
         */

    };
}
