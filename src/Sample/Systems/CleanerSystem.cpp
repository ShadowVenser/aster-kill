#include "CleanerSystem.h"

void CleanerSystem::OnUpdate()
{
    for (auto e: _PosStorage.Entities())
    {
        auto pos = _PosStorage.Get(e);
        if (pos.X <= -100 || pos.X >= (_windowSize.x + 100) || pos.Y <= -100 || pos.Y >= (_windowSize.y + 100))
            _KillMeStorage.Add(e, {});
    }
}