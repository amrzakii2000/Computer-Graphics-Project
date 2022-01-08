#include "shootingComponent.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our
{
    // Reads sensitivities & speedupFactor from the given json object
    void ShootingComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        speed = data.value("speed", speed);
    }
}