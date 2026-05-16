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
            switch (kse->code) {
                case sf::Keyboard::Key::Space: 
                {
                    if (!_states.x)
                    {
                        auto shootEventEntity = world.CreateEntity();
                        _shootEventComponent.Add(shootEventEntity, { });
                    }
                    break;
                }
                case sf::Keyboard::Key::Escape:
                {
                    _states.x = !_states.x;
                    break;
                }
                case sf::Keyboard::Key::I:
                {
                    _states.y = !_states.y;
                    break;
                }
                default:
                    continue;
            }
        }
    }
    _events.clear();
    
    if (_isPressed.x || _isPressed.y)
    {
        auto moveEventEntity = world.CreateEntity();
        _moveEventComponents.Add(moveEventEntity, {
            static_cast<uint8_t>(_isPressed.x ? 1 : 0),
            static_cast<uint8_t>(_isPressed.y ? 1 : 0)
        });
    }
}
