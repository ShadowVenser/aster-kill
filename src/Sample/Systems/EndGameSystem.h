#pragma once

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PlayerComponent.h"
#include "../Components/KillMeComponent.h"

class EndGameSystem: public ISystem
{
public:
    EndGameSystem(World& world, bool& isFaild):
        ISystem(world),
        _isFaild(isFaild),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _killMeStorage(world.GetStorage<KillMeComponent>())
    {}

    void OnInit() override {}
    void OnUpdate() override;

private:

    bool& _isFaild;
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<KillMeComponent>& _killMeStorage;

};