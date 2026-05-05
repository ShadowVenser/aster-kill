#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/MoveInputEventComponent.h"
#include "../Components/ShootEventComponent.h"

class InputSystem : public ISystem {

    std::vector<sf::Event>& _events;

    ComponentStorage<MoveInputEventComponent>& _moveEventComponents;
    ComponentStorage<ShootEventComponent>& _shootEventComponent;

public:
    InputSystem(World &world, std::vector<sf::Event>& events)
        : ISystem(world),
        _events(events),
        _moveEventComponents(world.GetStorage<MoveInputEventComponent>()),
        _shootEventComponent(world.GetStorage<ShootEventComponent>())

    {
    }

    void OnInit() override;

    void OnUpdate() override;
};

#endif //INPUTSYSTEM_H
