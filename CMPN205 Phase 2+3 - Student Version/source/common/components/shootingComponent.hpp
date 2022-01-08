#pragma once

#include "../ecs/component.hpp"

#include <glm/mat4x4.hpp>

namespace our
{
    // This component denotes that any renderer should draw the scene relative to this camera.
    // We do not define the eye, center or up here since they can be extracted from the entity local to world matrix
    class ShootingComponent: public Component
    {
    public:
        int speed = -20;

        // The ID of this component type is "Camera"
        static std::string getID() { return "Shooting"; }

        // Reads camera parameters from the given json object
        void deserialize(const nlohmann::json &data) override;
    };

}