#include "RenderSystem.h"

void RenderSystem::OnUpdate()
{
    _drawer->InitDraw();
    
    for (int e: _sprites.Entities())
    {
        auto& sprite = _sprites.Get(e);
        auto& pos = _positions.Get(e);
        if (_rotates.Has(e))
        {
            auto& rotate = _rotates.Get(e);
            _drawer->Draw(sprite.type, {pos.X, pos.Y}, sprite.sId, rotate.currentDegree);
        }
        else
        {
            _drawer->Draw(sprite.type, {pos.X, pos.Y});
        }
    }

    _drawer->Display();
}