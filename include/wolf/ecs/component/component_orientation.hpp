//
// Created by User on 9/21/2020.
//

#pragma once


#include <glm/fwd.hpp>
#include <glm/detail/type_vec4.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "component.hpp"

namespace Wolf::ECS {
    class ComponentTransform : public Wolf::ECS::Component {

    private:
        glm::mat4 m_t{1.0f}; //Translation
        glm::mat4 m_s{1.0f}; //Scale
        glm::mat4 m_r{1.0f}; //rotation
        glm::mat4 m_transform{1.0f}; //transform


    public:

        void reset();
        void apply();

        //TODO: This is not enough for Euler Angles, this will rotate around world axis, not local.
        void rotate(glm::vec3 axisToRotateAround, float angle, bool local = true);
    };
}