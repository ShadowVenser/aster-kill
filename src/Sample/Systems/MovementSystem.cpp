#include "MovementSystem.h"
#include "KillerSystem.h"
#include "../Components/KillMeComponent.h"

void MovementSystem::Print(int ent)
{
    auto& position = _positionComponents.Get(ent);

    std::cout << ent << " Pos: " << position.X << ", " << position.Y << std::endl;
}

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
