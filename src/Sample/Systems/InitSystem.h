#ifndef INITSYSTEM_H
#define INITSYSTEM_H

#include "../../Ecs/Systems/IInitializer.h"
#include "../../Objects/Config.h"
#include "../../Objects/Drawer.h"

class InitSystem final : public IInitializer {
public:
    InitSystem(World &world, const Config& cfg, Drawer& d) : IInitializer(world) 
    {
        _speed = cfg.cfg().at("player").at("speed").get<float>();
        _colliderRect = d.GetSpriteSize(my_game::type::Player);
        auto win = d.GetWindowSize();
        _initPos.x = (float)(win.x - _colliderRect.x) * cfg.cfg().at("player").at("pos").at("x").get<float>();
        _initPos.y = (float)(win.y - _colliderRect.y) * cfg.cfg().at("player").at("pos").at("y").get<float>();
    }

    void OnInit() override;
private:
    float _speed;
    my_game::vec2<int> _colliderRect;
    my_game::vec2<float> _initPos;
};



#endif //INITSYSTEM_H
