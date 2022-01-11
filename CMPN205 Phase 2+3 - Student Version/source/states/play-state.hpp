#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/movement.hpp>
#include <asset-loader.hpp>
#include <systems/shooting.hpp>
#include <systems/collision-controller.hpp>

// This state shows how to use the ECS framework and deserialization.
class Playstate : public our::State
{

    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::shooting shooting;
    our::CollisionSystem collision;


    bool checkWin()
    {
        //Checif there is  still some bugs
        for (auto& entity : world.getEntities())
        {
            if (entity->name == "bug")
                return false;
        }
        return true;
    }

    void onInitialize() override
    {
        // First of all, we get the scene configuration from the app config
        auto &config = getApp()->getConfig()["game"];
        // If we have assets in the scene config, we deserialize them
        if (config.contains("assets"))
        {
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if (config.contains("world"))
        {
            world.deserialize(config["world"]);
        }
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        shooting.enter(getApp());
        collision.enter(getApp());
    }

    void onDraw(double deltaTime) override
    {
        if (getApp()->getKeyboard().isPressed(GLFW_KEY_ESCAPE))
        { 
            getApp()->changeState("main-menu"); 
        }
            // Here, we just run a bunch of systems to control the world logic
        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        shooting.update(&world, (float)deltaTime);
        collision.update(&world, (float)deltaTime);

        // And finally we use the renderer system to draw the scene
        auto size = getApp()->getFrameBufferSize();
        renderer.render(&world, glm::ivec2(0, 0), size);

        //Check if the player won the game
        if (checkWin())
        {
            //Show win game state
            getApp()->changeState("win");
        }
    }

    void onDestroy() override
    {
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
        world.clear();
    }
};