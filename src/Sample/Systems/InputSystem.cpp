#include "InputSystem.h"

void InputSystem::OnInit()
{
}

void InputSystem::OnUpdate()
{
    for (auto e: _events)
    {
        if (auto kse = e.getIf<sf::Event::KeyPressed>(); kse)
        {
            // auto eventEntity = world.CreateEntity();
            // _eventComponents.Add(eventEntity, {});
        }
    }
    _events.clear();
}
