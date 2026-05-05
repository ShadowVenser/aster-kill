#include "InitSystem.h"

#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"

void InitSystem::OnInit()
{
    const int player = world.CreateEntity();

    auto& playerStorage = world.GetStorage<PlayerComponent>();
    auto& positionsStorage = world.GetStorage<PositionComponent>();
    auto& movementsStorage = world.GetStorage<MovementComponent>();
    auto& spriteStorage = world.GetStorage<SpriteComponent>();
    auto& boxColliderStorage = world.GetStorage<BoxColliderComponent>();

    playerStorage.Add(player, {.score = 0});
    positionsStorage.Add(player, PositionComponent(_initPos.x, _initPos.y));
    movementsStorage.Add(player, MovementComponent(_speed, {0, 0}));
    spriteStorage.Add(player, {.type=my_game::type::Player});
    boxColliderStorage.Add(player, {.w=_colliderRect.x, .h=_colliderRect.y});
}
