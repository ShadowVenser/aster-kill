#include "../Systems/MoveEventSystem.h"

void MoveEventSystem::OnUpdate()
{
    auto& player = _playerStorage.Entities()[0];
    auto& playerMovement = _movementComponents.Get(player);
    
    if (_moveEventComponents.Count() == 0)
        playerMovement.Direction = {0, 0};
    else
    {
        auto& fstEvent = _moveEventComponents.Entities()[0];
        auto dir = _moveEventComponents.Get(fstEvent).side;
        
        playerMovement.Direction.x = static_cast<float>(dir.y) - static_cast<float>(dir.x);

        for (auto& e: _moveEventComponents.Entities())
        {
            _killMeStorage.Add(e, { });
        }
    }
}
