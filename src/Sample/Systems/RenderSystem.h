#pragma once

#include <memory>

#include "../../Objects/Drawer.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/RotateComponent.h"
#include "../Components/SpriteComponent.h"


class RenderSystem: public ISystem {
public:
    RenderSystem(World& world, Drawer* drawer):
        ISystem(world), 
        _drawer(drawer),
        _positions(world.GetStorage<PositionComponent>()),
        _rotates(world.GetStorage<RotateComponent>()),
        _sprites(world.GetStorage<SpriteComponent>())
    {}

    void OnInit() override {}

    void OnUpdate() override;

private:
    Drawer* _drawer;

    ComponentStorage<PositionComponent>& _positions;
    ComponentStorage<RotateComponent>& _rotates;
    ComponentStorage<SpriteComponent>& _sprites;
};