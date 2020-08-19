//
// Created by User on 7/25/2020.
//

#pragma once
#include <wolf/pttrns/singleton.hpp>

namespace Wolf {

    class ID {
        inline static unsigned long sId{0};
        unsigned long mId{0};
    public:
        ID();
        unsigned long getId() const;

    };
}

