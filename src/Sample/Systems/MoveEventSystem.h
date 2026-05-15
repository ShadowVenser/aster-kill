#pragma once

#include "../../Ecs/Systems/ISystem.h"
#include "../Components/KillMeComponent.h"
#include "../Components/MoveInputEventComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"

#include "../../Ecs/Filter/FilterBuilder.h"


class MoveEventSystem: public ISystem 
{
public:
    MoveEventSystem(World& world, Drawer& d, const Config& c):
        ISystem(world),
        _killMeStorage(world.GetStorage<KillMeComponent>()),
        // _playerStorage(world.GetStorage<PlayerComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _movementComponents(world.GetStorage<MovementComponent>()),
        _moveEventComponents(world.GetStorage<MoveInputEventComponent>()),
        _borders
        (
            static_cast<float>(d.GetWindowSize().x) * c.cfg().at("player").at("borders").at("left").get<float>(),
            static_cast<float>(d.GetWindowSize().x) * c.cfg().at("player").at("borders").at("right").get<float>() - 
                static_cast<float>(d.GetSpriteSize(my_game::type::Player).x)
        )
    {
        FilterBuilder buildPosStorage(world);
        _playerPos = buildPosStorage
            .With<PositionComponent>()
            .With<PlayerComponent>()
            .With<MovementComponent>()
            .OptimisedBy<PositionComponent>()
            .Build();
    }

    void OnInit() override {}
    void OnUpdate() override;
private:

    ComponentStorage<KillMeComponent>& _killMeStorage;
    // ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<MoveInputEventComponent>& _moveEventComponents;
    std::shared_ptr<Filter> _playerPos;
    
    const my_game::vec2<float> _borders;
};