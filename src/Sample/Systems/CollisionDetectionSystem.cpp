#include "CollisionDetectionSystem.h"
#include <algorithm>

void CollisionDetectionSystem::OnUpdate()
{
    for (const auto boxId: _boxStorage.Entities())
    {
        auto& boxPos = _posStorage.Get(boxId);
        auto& box = _boxStorage.Get(boxId);

        for (const auto circleId: _circleStorage.Entities()) 
        {
            auto& circlePos = _posStorage.Get(circleId);
            auto& circle = _circleStorage.Get(circleId);

            float Dx = std::clamp(circlePos.X, boxPos.X, boxPos.X + box.w);
            float Dy = std::clamp(circlePos.Y, boxPos.Y, boxPos.Y + box.h);

            float deltaX = Dx - circlePos.X;
            float deltaY = Dy - circlePos.Y;

            if ((circle.R * circle.R) >= (deltaX * deltaX + deltaY * deltaY))
            {
                auto collision = world.CreateEntity();
                _collisionStorage.Add(collision, {.boxId=boxId, .circleId=circleId});
            }
        }
    }
}