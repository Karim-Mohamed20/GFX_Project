#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our {

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const {
        //TODO: (Req 3) Write this function
        // Here we make a translation matrix, a rotation matrix and a scaling matrix
        glm::mat4 Translation_Matrix = glm::translate(glm::mat4(1.0f), position); // we call translate with the identity matrix to make a translation matrix
        glm::mat4 Rotation_Matrix = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z); // we call yawPitchRoll to make a rotation matrix
        glm::mat4 Scale_Matrix = glm::scale(glm::mat4(1.0f), scale); // we call scale with the identity matrix to make a scaling matrix

        
        // the output of this function should be the product of the three matrices above in the correct order
        //  to apply the transformations 
        return Translation_Matrix * Rotation_Matrix * Scale_Matrix;
    }

     // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json& data){
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale    = data.value("scale", scale);
    }

}