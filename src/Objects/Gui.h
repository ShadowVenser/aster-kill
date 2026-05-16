#pragma once

#include <string>
#include <cxxabi.h>

#include "MyGame.h"

#include "imgui-SFML.h"

#include "../Ecs/World/World.h"

class Gui
{
public:
    Gui() = default;

    Gui(Gui&) = delete;
    Gui(Gui&&) = delete;
    Gui operator=(Gui&) = delete;
    Gui& operator=(Gui&&) = delete;

    void BindGui(my_game::GuiBinder&);
    void UpdateGui();
    void DrawGui();
private:
    std::string _GetDemangleNameById(int storageId);

    World* _world;
    bool* _visible;
    bool _prepared = false;

    my_game::vec2<float> _meanTimeBorders;
    my_game::vec2<float> _stdTimeBorders;

    float* _meanTime;
    float* _stdTime;
    bool* _spawner;

    sf::RenderWindow* _renderer;
    sf::Clock _deltaClock;
};