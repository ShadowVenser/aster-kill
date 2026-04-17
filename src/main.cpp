#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ecs/Components/BaseComponentStorage.h"
#include "Ecs/World/World.h"
#include "Ecs/Filter/FilterBuilder.h"
#include "Ecs/Components/ComponentStorage.hpp"

// #include "Ecs/Systems/SystemsManager.h"
// #include "Ecs/World/World.h"

// #include "Sample/Systems/InitSystem.h"
// #include "Sample/Systems/InputSystem.h"
// #include "Sample/Systems/MovementSystem.h"

// int main() {
//     // Пример использования
//     setlocale(LC_ALL, "");

//     const int wWidth = 1280;
//     const int wHeight = 720;
//     sf::RenderWindow window(sf::VideoMode({wWidth, wHeight}), "Test");
//     window.setFramerateLimit(60);

//     World world;
//     SystemsManager systems(world);
//     systems.AddInitializer(std::make_shared<InitSystem>(world));
//     systems.AddSystem(std::make_shared<InputSystem>(world, window));
//     systems.AddSystem(std::make_shared<MovementSystem>(world));

//     while (window.isOpen()) {
//         systems.Update();
//     }

//     return 0;
// }

struct Prop1 {};
struct Prop2 {};
struct Prop3 {};

int main() 
{
    World w {};

    auto st1 = w.GetRawStorage<Prop1>();
    auto st2 = w.GetRawStorage<Prop2>();
    auto st3 = w.GetRawStorage<Prop3>();

    int id1 = w.CreateEntity();
    int id2 = w.CreateEntity();
    int id3 = w.CreateEntity();
    int id4 = w.CreateEntity();
    int id5 = w.CreateEntity();
    int id6 = w.CreateEntity();
    int id7 = w.CreateEntity();

    st1->Add(id1, {});
    st1->Add(id3, {});
    st1->Add(id5, {});
    st1->Add(id7, {});

    st2->Add(id3, {});
    st2->Add(id6, {});
    st2->Add(id7, {});

    st3->Add(id4, {});
    st3->Add(id5, {});
    st3->Add(id6, {});
    st3->Add(id7, {});

    // auto filter = FilterBuilder(w).With<Prop2>().With<Prop3>().OptimisedBy<Prop3>().Build();
    auto f2 = FilterBuilder(w).Without<Prop1>().Build();

    st3->Add(id3, {});
    st2->Add(id2, {});

    w.RemoveEntity(id6);


    std::cout << "Hello World!";
}