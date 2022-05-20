#include "Game.h"
#include "../Component/TransformComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/AnimatedSpriteComponent.h"
#include "../System/AnimatedSpriteSystem.h"
#include "../System/MovementSystem.h"
#include "../System/RenderSystem.h"

void Prune::Game::InitECS()
{
    entt::registry m_Registry;
}

void Prune::Game::SetRenderer(SDL_Renderer* renderer)
{
    m_Renderer = renderer;
}

void Prune::Game::CaptureEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        /*switch (event.type)
        {
        }*/
    }
}

void Prune::Game::CreateEntities()
{
    // Default
    entt::entity entity1 = m_Registry.create();
    m_Registry.emplace<TransformComponent>(entity1, glm::vec2(10, 10), glm::vec2(1, 1));
    m_Registry.emplace<VelocityComponent>(entity1, glm::vec2(200, 0));
    m_Registry.emplace<SpriteComponent>(entity1, "sprite", 32, 32);

    // Crop of image
    entt::entity entity2 = m_Registry.create();
    m_Registry.emplace<TransformComponent>(entity2, glm::vec2(10, 50), glm::vec2(1.4, 1.4));
    m_Registry.emplace<VelocityComponent>(entity2, glm::vec2(200, 0));
    m_Registry.emplace<SpriteComponent>(entity2, "sprite", 32, 32);

    // To be animated
    entt::entity entity3 = m_Registry.create();
    m_Registry.emplace<TransformComponent>(entity3, glm::vec2(10, 120), glm::vec2(1, 1));
    m_Registry.emplace<VelocityComponent>(entity3, glm::vec2(200, 0));
    m_Registry.emplace<SpriteComponent>(entity3, "sprite", 32, 32);
    m_Registry.emplace<AnimatedSpriteComponent>(entity3, 1, 2, 8);
}

void Prune::Game::RunSystems(double delta)
{
    MovementSystem movementSystem = MovementSystem();
    movementSystem.Update(m_Registry, delta);

    AnimatedSpriteSystem animatedSpriteSystem = AnimatedSpriteSystem();
    animatedSpriteSystem.Update(m_Registry);
}

void Prune::Game::RenderEntities()
{
    RenderSystem renderSystem = RenderSystem();
    renderSystem.Update(m_Registry, m_Renderer);
}

void Prune::Game::RenderBackground()
{
    SDL_SetRenderDrawColor(m_Renderer, 80, 50, 185, 255);
    SDL_RenderClear(m_Renderer);
}
