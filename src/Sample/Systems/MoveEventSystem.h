#pragma once

#include "../../Ecs/Systems/ISystem.h"
#include "../Components/KillMeComponent.h"
#include "../Components/MoveInputEventComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"


class MoveEventSystem: public ISystem 
{
public:
    MoveEventSystem(World& world):
        ISystem(world),
        _killMeStorage(world.GetStorage<KillMeComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _movementComponents(world.GetStorage<MovementComponent>()),
        _moveEventComponents(world.GetStorage<MoveInputEventComponent>())
    {}

    void OnInit() override {}
    void OnUpdate() override;
private:

    ComponentStorage<KillMeComponent>& _killMeStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<MoveInputEventComponent>& _moveEventComponents;
    
};