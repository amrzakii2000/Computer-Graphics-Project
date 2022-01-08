#pragma once

#include "../ecs/world.hpp"
#include "../ecs/entity.hpp"
#include "../components/camera.hpp"
#include "../components/shootingComponent.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include<iostream>

namespace our
{

    // The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-camera-controller.hpp"
    class shooting
    {
        Application *app; // The application in which the state runs
        bool IsShot;
        float time;
    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
            IsShot = false;
        }
        
        void update(World *world, float deltaTime){
            Entity* fireball = nullptr;
            Entity* gun = nullptr;
            CameraComponent* camera = nullptr;
            ShootingComponent* shooting = nullptr;

            for (auto entity : world->getEntities())
            {
                if (entity->name == "revolver")
                {
                    gun = entity;
                }

                if(entity->getComponent<CameraComponent>() != nullptr){
                    camera = entity->getComponent<CameraComponent>();
                }

                if(entity->getComponent<ShootingComponent>() != nullptr){
                    shooting = entity->getComponent<ShootingComponent>();
                }
                
            }

            if (shooting)
                fireball = shooting->getOwner();

            if (!fireball|| !gun || !camera) return;

            time += deltaTime;
            if(time > 0.6){
                time = 0;
                IsShot = false;
                fireball->localTransform.position = gun->localTransform.position + glm::vec3(0, 0.2, 0.3);
            }
            //if space bar is pressed set the fireball position to gun position
            if (app->getKeyboard().isPressed(GLFW_KEY_E)) IsShot = true;

            if(IsShot){
                fireball->localTransform.position += deltaTime * glm::vec3(0, 0, shooting->speed);
            }
            
        }

        };
    }