#pragma once

#include "../../Ecs/Systems/ISystem.h"

#include "../../Objects/Drawer.h"

#include "../Components/KillMeComponent.h"
#include "../Components/PositionComponent.h"

class CleanerSystem: public ISystem 
{
    my_game::vec2<int> _windowSize;
    ComponentStorage<KillMeComponent>& _KillMeStorage;
    ComponentStorage<PositionComponent>& _PosStorage;

public:
    CleanerSystem(World &world, Drawer* drawer)
        : ISystem(world),
        _windowSize(drawer->GetWindowSize()),
        _KillMeStorage(world.GetStorage<KillMeComponent>()),
        _PosStorage(world.GetStorage<PositionComponent>())
    {}

    void OnInit() override {}

    void OnUpdate() override;
};