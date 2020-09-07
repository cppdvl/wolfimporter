//
// Created by User on 8/19/2020.
//

#ifndef WOLF_ECSNODE_HPP
#define WOLF_ECSNODE_HPP
#include <wolf/id.hpp>
namespace Wolf::ECS {

    class ECSNode : public Wolf::ID{
    public:
        ECSNode() : Wolf::ID(){

        }

    };

    using SPECSNode = std::shared_ptr<Wolf::ECS::ECSNode>;

}


#endif //WOLF_ECSNODE_HPP
