#pragma once

#include "../Components/KillMeComponent.h"
#include "../../Ecs/Systems/ISystem.h"

class KillerSystem final : public ISystem {
    ComponentStorage<KillMeComponent>& _clients;

public:
    KillerSystem(World &world)
        : ISystem(world),
            _clients(world.GetStorage<KillMeComponent>())
    {}

    void OnInit() override;

    void OnUpdate() override;
};
