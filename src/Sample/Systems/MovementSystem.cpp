#include "MovementSystem.h"


void MovementSystem::OnUpdate()
{
    for (const auto ent : _moveables->GetView())
    {
        auto& position = _positionComponents.Get(ent);
        auto& movement = _movementComponents.Get(ent);

        position.X += movement.Speed * movement.Direction.x;
        position.Y += movement.Speed * movement.Direction.y;
    }

    for (auto e: _rotateComponent.Entities())
    {
        auto& rotate = _rotateComponent.Get(e);
        rotate.currentDegree = static_cast<int>(rotate.currentDegree + rotate.rotateSpeed + 360) % 360;
    }
}
