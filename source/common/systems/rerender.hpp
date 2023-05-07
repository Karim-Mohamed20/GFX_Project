#pragma once

#include "../ecs/world.hpp"
#include "../components/rerender.hpp"
#include "../components/free-camera-controller.hpp"


#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include <iostream>

namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic. 
    // For more information, see "common/components/movement.hpp"
    class RerenderSystem {
    public:

        // This should be called every frame to update all entities containing a MovementComponent. 
        void update(World* world, float deltaTime) {
          FreeCameraControllerComponent *controller = nullptr;

          for(auto entity : world->getEntities()){
                // Get the Car
                controller = entity->getComponent<FreeCameraControllerComponent>();
                if(controller)break;
            }

            // For each entity in the world
            for(auto entity : world->getEntities()){
                // Get the movement component if it exists
                RerenderComponent* Rerender = entity->getComponent<RerenderComponent>();

                // If the movement component exists
                if(Rerender && controller){
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    // std::cout<<entity->localTransform.position.z<<"\n";
                    if((controller->getOwner()->localTransform.position.z < Rerender->getOwner()->localTransform.position.z)){
                      Rerender->getOwner()->localTransform.position.z -=5;
                    // std::cout<<entity->localTransform.position.z<<"\n";

                    }
                }
            }
        }

    };

}
