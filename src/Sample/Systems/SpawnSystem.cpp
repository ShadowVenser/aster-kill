#include "SpawnSystem.h"

void SpawnSystem::OnUpdate()
{
    if (_isPaused)
    {
        _spawnTimer.pause();
        return;
    }
    if (_spawnTimer.isEvent() || _needOneMoreAsteroid)
    {
        auto props = _drawer->GetAsteroid();
        auto aId = world.CreateEntity();

        _AsteroidComponentStorage.Add(aId, {props.score});
        _CircleColliderComponentStorage.Add(aId, {static_cast<float>(props.collisionR)});
        _MovementComponentStorage.Add(aId, {props.speed, props.dir});
        _PositionComponentStorage.Add(aId, {props.pos.x, props.pos.y});
        _RotateComponentStorage.Add(aId, {0, props.rotateSpeed});
        _SpriteComponentStorage.Add(aId, {my_game::type::Asteroid, props.spriteId});

        _needOneMoreAsteroid = false;
    }
}