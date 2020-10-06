//
// Created by User on 9/21/2020.
//

#include <glm/detail/type_vec3.hpp>
#include <wolf/ecs/component/component_orientation.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>


void Wolf::ECS::ComponentTransform::apply() {

    m_transform = m_t * m_r * m_s;

}

void Wolf::ECS::ComponentTransform::reset() {

    m_s = glm::mat4 {1.0f}; //POS : 0, 0, 0
    m_r = glm::rotate(glm::mat4 (), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f)); //
    m_t = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f)); //SCL : 1, 1, 1
    apply();

}

void Wolf::ECS::ComponentTransform::rotate(glm::vec3 axisToRotateAround, float angle, bool local){

    //I want to rotate using the rotated axes a.k.a. local coordinate, of the object.
    if (local) m_r = glm::rotate(m_r, angle, axisToRotateAround);
    //I want to rotate using an axis referenced to the world coordinate system.
    else {
        auto rotateAroundNonLocalAxis = glm::rotate(glm::mat4(), angle, axisToRotateAround);
        m_r = rotateAroundNonLocalAxis * m_r;
    }
}

