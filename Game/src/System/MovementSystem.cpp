#include "MovementSystem.h"
#include "../Component/TransformComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Log/Log.h"

void Prune::MovementSystem::Update(entt::registry& registry, double delta)
{
    auto view = registry.view<TransformComponent, VelocityComponent>();

    for (auto entity : view) {
        TransformComponent& transformComponent = view.get<TransformComponent>(entity);
        VelocityComponent& velocityComponent = view.get<VelocityComponent>(entity);

        transformComponent.position.x += static_cast<int>(velocityComponent.velocity.x * delta);
        transformComponent.position.y += static_cast<int>(velocityComponent.velocity.y * delta);

        PRUNE_LOG_INFO("Position of entity {0} set to x: {0}, y: {1}", static_cast<int>(entity), transformComponent.position.x, transformComponent.position.y);
    }
};
