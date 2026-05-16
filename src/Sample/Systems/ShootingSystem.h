#pragma once

#include "../../Ecs/Systems/ISystem.h"

#include "../../Objects/Config.h"
#include "../../Objects/Timer.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/KillMeComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/ShootEventComponent.h"
#include "../Components/SpriteComponent.h"


class ShootingSystem: public ISystem
{
public:
    ShootingSystem(World& world, Drawer& d, const Config& cfg, bool& isPaused):
        ISystem(world),
        
        _CooldownTimer([time= cfg.cfg().at("bullet").at("cooldown").get<int>()](){
            return sf::milliseconds(time);
        }),
        _speedValue(cfg.cfg().at("bullet").at("speed").get<float>()),
        _boxSize(d.GetSpriteSize(my_game::type::Bullet)),

        _boxColliderStorage(world.GetStorage<BoxColliderComponent>()),
        _bulletStorage(world.GetStorage<BulletComponent>()),
        _killMeStorage(world.GetStorage<KillMeComponent>()),
        _movementStorage(world.GetStorage<MovementComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _positionStorage(world.GetStorage<PositionComponent>()),
        _shootEvents(world.GetStorage<ShootEventComponent>()),
        _spriteStorage(world.GetStorage<SpriteComponent>()),
        _isPaused(isPaused)
    { }

    void OnInit() override { }
    void OnUpdate() override;

private:
    Timer _CooldownTimer;
    
    float _speedValue;
    my_game::vec2<int> _boxSize;

    ComponentStorage<BoxColliderComponent>& _boxColliderStorage;
    ComponentStorage<BulletComponent>& _bulletStorage;
    ComponentStorage<KillMeComponent>& _killMeStorage;
    ComponentStorage<MovementComponent>& _movementStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<PositionComponent>& _positionStorage;
    ComponentStorage<ShootEventComponent>& _shootEvents;
    ComponentStorage<SpriteComponent>& _spriteStorage;

    bool& _isPaused;

};