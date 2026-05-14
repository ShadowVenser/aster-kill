#include "HitSystem.h"
#include <unordered_set>

void HitSystem::OnUpdate()
{
    if (_collisionStorage.Count() > 0)
    {
        auto& score = _playerStorage.Get(_playerStorage.Entities()[0]).score;
        
        std::unordered_set<int> realisedCollisions;

        for (auto collisionId: _collisionStorage.Entities())
        {
            auto collision = _collisionStorage.Get(collisionId);
            if (!realisedCollisions.contains(collision.boxId) 
                && !realisedCollisions.contains(collision.circleId))
            {
                _killMeStorage.Add(collision.boxId, { });
                _killMeStorage.Add(collision.circleId, { });

                realisedCollisions.insert(collision.boxId);
                realisedCollisions.insert(collision.circleId);

                if (!_playerStorage.Has(collision.boxId))
                    score += _asteroidStorage.Get(collision.circleId).score;
            }
            _killMeStorage.Add(collisionId, { });
        }

        _setScore(score);
    }
}