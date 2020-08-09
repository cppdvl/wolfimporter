//
// Created by User on 7/25/2020.
//

#ifndef WOLF_ID_HPP
#define WOLF_ID_HPP
#include <wolf/pttrns/singleton.hpp>

namespace Wolf::Engine {

    class ID : public Wolf::Pttrn::Singleton<Wolf::Engine::ID>{
        inline static unsigned long sId{0};
        unsigned long mId{0};
    public:
        ID();
        unsigned long getId() const;

    };
}

#endif //WOLF_ID_HPP
