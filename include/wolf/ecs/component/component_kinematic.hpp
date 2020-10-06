//
// Created by User on 9/19/2020.
//

#pragma once

#include "component.hpp"
#include "../../../../Vendor/glm/glm/fwd.hpp"
#include "../../../../Vendor/glm/glm/detail/type_vec3.hpp"

namespace Wolf::ECS {

    class ComponentKinematic : public Wolf::ECS::Component {
    private:
        glm::vec3 mlocation{0.0f, 0.0f, 0.0f};
        glm::vec3 mspeed{0.0f, 0.0f, 0.0f};
        glm::vec3 macceleration{0.0f, 0.0f, 0.0f};
    public:


        void setLocation(float, float, float);
        void setLocation(const glm::vec3&);
        void setSpeed(float, float, float);
        void setSpeed(const glm::vec3&);
        void setAcceleration(float, float, float);
        void setAcceleration(const glm::vec3&);

        inline const glm::vec3& getLocation() { return mlocation; }
        inline const glm::vec3& getSpeed() { return mspeed; }
        inline const glm::vec3& getAcceleration() { return macceleration; }


    };

}