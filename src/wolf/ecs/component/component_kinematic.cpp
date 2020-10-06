//
// Created by User on 9/22/2020.
//


#include <glm/fwd.hpp>
#include <wolf/ecs/component/component_kinematic.hpp>

void Wolf::ECS::ComponentKinematic::setLocation(const glm::vec3& location) {
    mlocation = location;
}

void Wolf::ECS::ComponentKinematic::setLocation(float x, float y, float z) {
    mlocation = glm::vec3(x, y, z);
}

void Wolf::ECS::ComponentKinematic::setSpeed(const glm::vec3& speed) {
    mspeed = speed;
}

void Wolf::ECS::ComponentKinematic::setSpeed(float x, float y, float z) {
    mlocation = glm::vec3(x, y, z);
}

void Wolf::ECS::ComponentKinematic::setAcceleration(const glm::vec3& acceleration) {
    macceleration = acceleration;
}

void Wolf::ECS::ComponentKinematic::setAcceleration(float x, float y, float z) {
    macceleration = glm::vec3(x, y, z);
}


