#pragma once

#include "../../Ecs/Systems/ISystem.h"
#include "../../Objects/Drawer.h"
#include "../../Objects/Timer.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/RotateComponent.h"
#include "../Components/SpriteComponent.h"

class SpawnSystem final: public ISystem {

    Drawer* _drawer;
    Timer _spawnTimer;

    ComponentStorage<AsteroidComponent>&        _AsteroidComponentStorage;
    ComponentStorage<CircleColliderComponent>&  _CircleColliderComponentStorage;
    ComponentStorage<MovementComponent>&        _MovementComponentStorage;
    ComponentStorage<PositionComponent>&        _PositionComponentStorage;
    ComponentStorage<RotateComponent>&          _RotateComponentStorage;  
    ComponentStorage<SpriteComponent>&          _SpriteComponentStorage;

public:
    SpawnSystem(World &world, Drawer* drawer)
        : ISystem(world),
        _drawer(drawer),
        _spawnTimer(drawer->CreateSpawnTimeGetter()),
        _AsteroidComponentStorage(world.GetStorage<AsteroidComponent>()),
        _CircleColliderComponentStorage(world.GetStorage<CircleColliderComponent>()),
        _MovementComponentStorage(world.GetStorage<MovementComponent>()),
        _PositionComponentStorage(world.GetStorage<PositionComponent>()),
        _RotateComponentStorage(world.GetStorage<RotateComponent>()),
        _SpriteComponentStorage(world.GetStorage<SpriteComponent>())
    {
        
    }

    void OnInit() override {}

    void OnUpdate() override;
};