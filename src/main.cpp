#include <iostream>
#include <SFML/Graphics.hpp>

#include "Ecs/Systems/SystemsManager.h"
#include "Ecs/World/World.h"

#include "Sample/Systems/InitSystem.h"
#include "Sample/Systems/InputSystem.h"
#include "Sample/Systems/MovementSystem.h"

int main() {
    // Пример использования
    setlocale(LC_ALL, "");

    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "Test");
    window.setFramerateLimit(60);

    World world;
    SystemsManager systems(world);
    systems.AddInitializer(std::make_shared<InitSystem>(world));
    systems.AddSystem(std::make_shared<InputSystem>(world, window));
    systems.AddSystem(std::make_shared<MovementSystem>(world));

    while (window.isOpen()) {
        systems.Update();
    }

    return 0;
}