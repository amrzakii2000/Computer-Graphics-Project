#pragma once

#include "../ecs/world.hpp"
#include "../ecs/entity.hpp"
#include "../components/camera.hpp"
#include "../components/shootingComponent.hpp"
#include "../components/collider.hpp"


#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include<iostream>
using namespace std;

namespace our
{

    // The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-camera-controller.hpp"
    class shooting
    {
        Application *app; // The application in which the state runs
        float time;

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;

            //Set the time to delete the fireball
            time = 0;
        }
        
        void update(World *world, float deltaTime)
        {
            Entity* fireball = nullptr;
            Entity* gun = nullptr;
            ShootingComponent* shooting = nullptr;

            for (auto entity : world->getEntities())
            {
                //If we have a shooting component
                if(entity->getComponent<ShootingComponent>() != nullptr){
                    shooting = entity->getComponent<ShootingComponent>();
                }

                //If we have a revolver entity
                if (entity->name == "revolver") {
                    gun = entity;
                }

                // If we have a fireball entity
                if (entity->name == "fireball") {
                    fireball = entity;
                }
                
            }

            if (!shooting || !gun) return;

            //Create a new fireball on key press
            if (app->getKeyboard().isPressed(GLFW_KEY_R) && !fireball)
            {
                Entity* fireball = world->add();
                fireball->name = "fireball";
                fireball->parent = gun;
                fireball->localTransform.position = gun->localTransform.position + glm::vec3(-0.5, 0.2, -0.5);
                fireball->localTransform.scale = glm::vec3(0.001f, 0.001f, 0.001f);
                fireball->localTransform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
            }
            else if (fireball)
            {
                //Add the components of the fireball entity
                auto meshRenderer = fireball->addComponent<MeshRendererComponent>();
                meshRenderer->mesh = AssetLoader<Mesh>::get("fireBall");
                meshRenderer->material = AssetLoader<Material>::get("fireBall");

                auto movement = fireball->addComponent<MovementComponent>();
                movement->linearVelocity = glm::vec3(0, 0, shooting->speed);

                auto collider = fireball->addComponent<Collider>();
                collider->radius = 1.3f;

                //Delete teh fireball after some time
                if (time > 0.8)
                {
                    world->markForRemoval(fireball);
                    time = 0;
                }
            }
            time += deltaTime;
        }

     };
}