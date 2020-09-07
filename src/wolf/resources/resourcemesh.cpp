//
// Created by User on 7/26/2020.
//


#include <array>
#include <cassert>
#include <glm/glm.hpp>
#include <wolf/resources/resourcemesh.hpp>

using TriangleFace = std::vector<glm::uvec3>;
using Vertices = std::vector<glm::vec3>;
using Colors = Vertices;
using namespace Wolf::Resources;


static std::vector<glm::vec3> sCalculateNormals(Vertices vertices){

    auto verticessize = vertices.size();
    assert(verticessize % 3 == 0 && verticessize >= 3);

    std::vector<glm::vec3> normals{};
    for (auto triangleindex = 0ul; triangleindex < verticessize; triangleindex +=3){

        auto v0 = vertices[triangleindex + 0];
        auto v1 = vertices[triangleindex + 1];
        auto v2 = vertices[triangleindex + 2];
        auto normal = glm::cross(v1 - v0, v2 - v0);
        normals.push_back(normal);
    }
    assert(normals.size() == verticessize / 3);
    return normals;

}

static void sPopulateResourceMeshData(
        Wolf::Resources::ResourceMeshData& meshData,
        Vertices vertices,
        Colors colors,
        Wolf::Resources::ResourceMeshData::BufferLayout xBufferLayout){

    bool isVN = xBufferLayout == ResourceMeshData::BufferLayout::VN;
    bool isVNC = xBufferLayout == ResourceMeshData::BufferLayout::VNC;
    bool isVCN = xBufferLayout == ResourceMeshData::BufferLayout::VCN;
    bool isVC = xBufferLayout == ResourceMeshData::BufferLayout::VC;
    bool isV = xBufferLayout == ResourceMeshData::BufferLayout::V;

    auto nvertices = vertices.size();
    assert(vertices.size() >= 3);

    /* Calculate normals if needed */
    std::vector<glm::vec3> normals{};
    bool usesNormal = isVN || isVCN || isVNC;
    if(usesNormal) normals = sCalculateNormals(vertices);
    auto normalindex{0};
    for (auto index = 0ul; index < nvertices; ++index){
        if(normalindex % 3 == 0 && index > 0) normalindex++;
        meshData.push_back(vertices[index].x);
        meshData.push_back(vertices[index].y);
        meshData.push_back(vertices[index].z);
        if (isV) continue;
        else if (isVC || isVN){

            auto _2 = isVC ? colors[index] : normals[normalindex];
            meshData.push_back(_2.x);
            meshData.push_back(_2.y);
            meshData.push_back(_2.z);

        } else if (isVCN || isVNC){

            auto _2 = isVCN ? colors[index] : normals[normalindex];
            auto _3 = isVNC ? colors[index] : normals[normalindex];
            meshData.push_back(_2.x);
            meshData.push_back(_2.y);
            meshData.push_back(_2.z);
            meshData.push_back(_3.x);
            meshData.push_back(_3.y);
            meshData.push_back(_3.z);
        }
    }
}

static void sPopulateResourceMeshDataFacesVersion(
        Wolf::Resources::ResourceMeshData& meshData,
        Vertices vertices,
        Colors colors,
        Wolf::Resources::ResourceMeshData::BufferLayout xBufferLayout){

    /* Makes sense to have a color in the vertex, even if this vertex is shared by several faces */
    auto isVC = xBufferLayout == ResourceMeshData::BufferLayout::VC;
    auto isV = xBufferLayout == ResourceMeshData::BufferLayout::V;
    assert(isVC || isV);

    /* Check colors and vertices are same quantity -- if VC -- */
    auto nvertices = vertices.size();
    auto ncolors = colors.size();
    if (isVC) assert(ncolors == nvertices);

    /* Push vertices */
    for (auto vertexindex = 0ul; vertexindex < nvertices; ++vertexindex){
        auto vertex = vertices[vertexindex];
        meshData.push_back(vertex.x);
        meshData.push_back(vertex.y);
        meshData.push_back(vertex.z);
        if (isVC){
            auto& colorindex = vertexindex;
            auto color = colors[colorindex];
            meshData.push_back(color.x);
            meshData.push_back(color.y);
            meshData.push_back(color.z);
        }
    }


}

ResourceMeshData::ResourceMeshData(
        const std::vector<glm::vec3>&   vertices,
        const std::vector<glm::vec3>&   colors,
        const std::vector<glm::uvec3>&  faces,
        ResourceMeshData::BufferLayout  layout) : mBufferLayout(layout), mHasFaces(!faces.empty()){

    auto nvertices = vertices.size();
    assert(nvertices % 3 == 0 && nvertices >= 3);
    auto ncolors = colors.size();
    assert(ncolors == nvertices);




    if (mHasFaces){
        /* Push faces */
        for (auto& face : faces){
            mFaceIndices.push_back(face.x);
            mFaceIndices.push_back(face.y);
            mFaceIndices.push_back(face.z);
        }
        sPopulateResourceMeshDataFacesVersion(*this, vertices, colors, mBufferLayout);
    } else {

        sPopulateResourceMeshData(*this, vertices, colors, layout);
    }

}

