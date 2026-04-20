#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <memory>

#include "../../Ecs/Filter/Filter.h"
#include "../../Ecs/Filter/FilterBuilder.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/MoveInputEvent.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/RotateComponent.h"

class MovementSystem final : public ISystem {
    ComponentStorage<PositionComponent>& _positionComponents;
    ComponentStorage<MovementComponent>& _movementComponents;
    ComponentStorage<RotateComponent>& _rotateComponent;

    std::shared_ptr<Filter> _moveables;
    std::shared_ptr<Filter> _moveInputEvents;



    void Print(int ent);  // Это тоже можно вынести в отдельную систему

public:
    MovementSystem(World &world)
        : ISystem(world),
            _positionComponents(world.GetStorage<PositionComponent>()),
            _movementComponents(world.GetStorage<MovementComponent>()),
            _rotateComponent(world.GetStorage<RotateComponent>()),
            _moveables(FilterBuilder(world)
                .With<PositionComponent>()
                .With<MovementComponent>()
                .Build()),
            _moveInputEvents(FilterBuilder(world)
                .With<MoveInputEvent>()
                .Build())
    {
    }

    void OnInit() override {}

    void OnUpdate() override;
};

#endif //MOVEMENTSYSTEM_H
