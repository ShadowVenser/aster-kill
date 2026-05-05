#include "InputSystem.h"
#include "SFML/Window/Keyboard.hpp"

void InputSystem::OnInit()
{
}

void InputSystem::OnUpdate()
{
    for (auto e: _events)
    {
        if (auto kse = e.getIf<sf::Event::KeyPressed>(); kse)
        {
            auto eventEntity = world.CreateEntity();
            switch (kse->code) {
                case sf::Keyboard::Key::Left:
                    _moveEventComponents.Add(eventEntity, {1, 0});
                    break;
                case sf::Keyboard::Key::Right:
                    _moveEventComponents.Add(eventEntity, {0, 1});
                    break;
                case sf::Keyboard::Key::Space:
                    _shootEventComponent.Add(eventEntity, { });
                    break;
                default:
                    world.RemoveEntity(eventEntity);
            }
        }
    }
    _events.clear();
}
