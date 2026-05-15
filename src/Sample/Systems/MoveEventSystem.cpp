#include "../Systems/MoveEventSystem.h"

void MoveEventSystem::OnUpdate()
{
    for (auto player: _playerPos->GetView())
    {
    // auto player = _playerStorage.Entities()[0];
        auto& playerMovement = _movementComponents.Get(player);
        
        auto playerPos = _posStorage.Get(player).X;

        if (_moveEventComponents.Count() == 0)
            playerMovement.Direction = {0, 0};
        else
        {
            auto fstEvent = _moveEventComponents.Entities()[0];
            auto dir = _moveEventComponents.Get(fstEvent).side;

            dir.x = playerPos > _borders.x ? dir.x : 0;
            dir.y = playerPos < _borders.y ? dir.y : 0;
            
            playerMovement.Direction.x = static_cast<float>(dir.y) - static_cast<float>(dir.x);

            for (auto& e: _moveEventComponents.Entities())
            {
                _killMeStorage.Add(e, { });
            }
        }
    }
}
