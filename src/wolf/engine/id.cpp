//
// Created by User on 7/25/2020.
//

#include "wolf/engine/id.hpp"
Wolf::Engine::ID::ID() {
    mId = ++sId;
}
unsigned long Wolf::Engine::ID::getId() const {
    return mId;
}