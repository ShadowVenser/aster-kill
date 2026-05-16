#include <SFML/Graphics.hpp>
#include <memory>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"

#include "Objects/Config.h"
#include "Objects/Drawer.h"
#include "Objects/Gui.h"
#include "Sample/Systems/CleanerSystem.h"
#include "Sample/Systems/EndGameSystem.h"
#include "Sample/Systems/InitSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/KillerSystem.h"
#include "Sample/Systems/MoveEventSystem.h"
#include "Sample/Systems/MovementSystem.h"
#include "Sample/Systems/RenderSystem.h"
#include "Sample/Systems/SpawnSystem.h"
#include "Sample/Systems/CollisionDetectionSystem.h"
#include "Sample/Systems/ShootingSystem.h"
#include "Sample/Systems/HitSystem.h"


int main() {
    // Пример использования
    setlocale(LC_ALL, "");

    const Config config("config.json");
    std::vector<sf::Event> events;
    my_game::vec2<bool> isPressed {.x=false, .y=false};
    bool isFailed = false;
    bool needOneMoreAsteroid = false;
    my_game::vec2<bool> states = {false, false};

    Drawer d(config);
    
    World world;

    my_game::GuiBinder binder;
    d.BindGui(binder);
    binder.isGuiVisible = &states.y;
    binder.world = &world;
    binder.spawner = &needOneMoreAsteroid;

    Gui gui;
    gui.BindGui(binder);

    SystemsManager systems(world);
    systems.AddInitializer(std::make_shared<InitSystem>(world, config, d));

    systems.AddSystem(std::make_shared<InputSystem>(world, events, isPressed, states));
    
    systems.AddSystem(std::make_shared<MoveEventSystem>(world, d, config));
    systems.AddSystem(std::make_shared<MovementSystem>(world, states.x));
    
    systems.AddSystem(std::make_shared<SpawnSystem>(world, &d, states.x, needOneMoreAsteroid));
    systems.AddSystem(std::make_shared<ShootingSystem>(world, d, config, states.x));

    systems.AddSystem(std::make_shared<CleanerSystem>(world, &d));
    
    systems.AddSystem(std::make_shared<RenderSystem>(world, &d, gui));

    systems.AddSystem(std::make_shared<CollisionDetectionSystem>(world));
    systems.AddSystem(std::make_shared<HitSystem>(world, d));
    systems.AddSystem(std::make_shared<EndGameSystem>(world, isFailed));
    
    systems.AddSystem(std::make_shared<KillerSystem>(world));

    while (d.isOpen() && !isFailed) 
    {
        d.pollEvent(events, isPressed);
        gui.UpdateGui();
        systems.Update();
    }

    while (d.isOpen())
    {
        d.pollEvent(events, isPressed);
        d.DrawGameOver();
        events.clear();
    }

    return 0;
}