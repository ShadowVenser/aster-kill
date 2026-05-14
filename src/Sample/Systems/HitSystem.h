#pragma once

#include <functional>
#include "../../Ecs/Systems/ISystem.h"

#include "../../Objects/Drawer.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/KillMeComponent.h"
#include "../Components/PlayerComponent.h"

class HitSystem: public ISystem
{
public:
    HitSystem(World& world, Drawer& d):
        ISystem(world),
        _asteroidStorage(world.GetStorage<AsteroidComponent>()),
        _collisionStorage(world.GetStorage<CollisionComponent>()),
        _killMeStorage(world.GetStorage<KillMeComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _setScore([&d](int score){d.SetScore(score);})
    {}

    void OnInit() override { }
    void OnUpdate() override;

private:

    ComponentStorage<AsteroidComponent>& _asteroidStorage;
    ComponentStorage<CollisionComponent>& _collisionStorage;
    ComponentStorage<KillMeComponent>& _killMeStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
    
    std::function<void(int)> _setScore;
};