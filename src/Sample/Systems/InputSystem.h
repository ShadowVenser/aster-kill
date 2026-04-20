#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SFML/Graphics.hpp>

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/MoveInputEvent.h"

class InputSystem : public ISystem {

    std::vector<sf::Event>& _events; // так делать не надо точно

    ComponentStorage<MoveInputEvent>& _eventComponents;

public:
    InputSystem(World &world, std::vector<sf::Event>& events)
        : ISystem(world),
        _events(events),
        _eventComponents(world.GetStorage<MoveInputEvent>())
    {

    }

    void OnInit() override;

    void OnUpdate() override;
};



#endif //INPUTSYSTEM_H
