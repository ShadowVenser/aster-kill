#include "ShootingSystem.h"

void ShootingSystem::OnUpdate()
{
    if (_shootEvents.Count() > 0)
    {
        if (_isPaused)
        {
            _CooldownTimer.pause();
        }
        else if (_CooldownTimer.isEvent())
        {
            auto bullet = world.CreateEntity();

            _boxColliderStorage.Add(bullet, {.w=_boxSize.x, .h=_boxSize.y});
            _bulletStorage.Add(bullet, { });
            _movementStorage.Add(bullet, {.Speed=_speedValue, .Direction={.x=0, .y=-1}});
            
            auto player = _positionStorage.Entities()[0];
            const auto& playerPosition = _positionStorage.Get(player);
            const auto& playerBox = _boxColliderStorage.Get(player);

            my_game::vec2<float> bulletPosition;
            bulletPosition.x = playerPosition.X + (static_cast<float>(playerBox.w - _boxSize.x) / 2.f);
            bulletPosition.y = playerPosition.Y - static_cast<float>(_boxSize.y);

            _positionStorage.Add(bullet, {bulletPosition.x, bulletPosition.y});
            _spriteStorage.Add(bullet, {my_game::type::Bullet});
        }

        for (auto event: _shootEvents.Entities())
        {
            _killMeStorage.Add(event, { });
        }
    }
}