#pragma once

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/CircleColliderComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/PositionComponent.h"

class CollisionDetectionSystem: public ISystem
{
public:
    CollisionDetectionSystem(World& world):
        ISystem(world),
        _boxStorage(world.GetStorage<BoxColliderComponent>()),
        _circleStorage(world.GetStorage<CircleColliderComponent>()),
        _collisionStorage(world.GetStorage<CollisionComponent>()),
        _posStorage(world.GetStorage<PositionComponent>())
    {}

    void OnInit() override {}
    void OnUpdate() override;

private:

    ComponentStorage<BoxColliderComponent>& _boxStorage;
    ComponentStorage<CircleColliderComponent>& _circleStorage;
    ComponentStorage<CollisionComponent>& _collisionStorage;
    ComponentStorage<PositionComponent>& _posStorage;

};