#include "EndGameSystem.h"

void EndGameSystem::OnUpdate()
{
    static const auto _player = _playerStorage.Entities()[0];
    _isFaild |= _killMeStorage.Has(_player);
}
