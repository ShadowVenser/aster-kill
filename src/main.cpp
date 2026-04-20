#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"

#include "Objects/Config.h"
#include "Objects/Drawer.h"
#include "Sample/Systems/CleanerSystem.h"
#include "Sample/Systems/InitSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/KillerSystem.h"
#include "Sample/Systems/MovementSystem.h"
#include "Sample/Systems/RenderSystem.h"
#include "Sample/Systems/SpawnSystem.h"
#include "nlohmann/json_fwd.hpp"


int main() {
    // Пример использования
    setlocale(LC_ALL, "");

    const Config config("config.json");
    std::vector<sf::Event> events;

    Drawer d(config);
    
    World world;
    SystemsManager systems(world);
    // systems.AddInitializer(std::make_shared<InitSystem>(world));
    // systems.AddSystem(std::make_shared<InputSystem>(world, events));

    systems.AddSystem(std::make_shared<CleanerSystem>(world, &d));
    systems.AddSystem(std::make_shared<SpawnSystem>(world, &d));
    systems.AddSystem(std::make_shared<RenderSystem>(world, &d));
    systems.AddSystem(std::make_shared<MovementSystem>(world));
    systems.AddSystem(std::make_shared<KillerSystem>(world));

    while (d.isOpen()) {
        d.pollEvent(events);
        systems.Update();
    }

    return 0;
}