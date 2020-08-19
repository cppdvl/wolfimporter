//
// Created by User on 7/26/2020.
//

#ifndef WOLF_RESOURCEMESH_HPP
#define WOLF_RESOURCEMESH_HPP
#include <wolf/resources/resourcemanager.hpp>

namespace Wolf::Engine {
    class ResourceMesh : public Wolf::Engine::Resource {
        unsigned long mvao;
    public:
        const unsigned long& GetVAO() const;
    };
}
#endif //WOLF_RESOURCEMESH_HPP
