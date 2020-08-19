//
// Created by User on 7/25/2020.
//

#include <wolf/id.hpp>
Wolf::ID::ID() {
    mId = ++sId;
}
unsigned long Wolf::ID::getId() const {
    return mId;
}