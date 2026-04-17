#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"

#include "Objects/Config.h"
#include "Sample/Systems/InitSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/KillerSystem.h"
#include "Sample/Systems/MovementSystem.h"


int main() {
    // Пример использования
    setlocale(LC_ALL, "");

    Config::Init("config.json");

    const unsigned int wWidth = Config::cfg().at("window").at("width").get<unsigned int>();
    const unsigned int wHeight = Config::cfg().at("window").at("height").get<unsigned int>();
    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "Test");
    window.setFramerateLimit(60);

    World world;
    SystemsManager systems(world);
    systems.AddInitializer(std::make_shared<InitSystem>(world));
    systems.AddSystem(std::make_shared<InputSystem>(world, window));
    systems.AddSystem(std::make_shared<MovementSystem>(world));
    systems.AddSystem(std::make_shared<KillerSystem>(world));

    while (window.isOpen()) {
        systems.Update();
    }

    return 0;
}