#pragma once

#include <functional>
#include <memory>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Randomiser.h"
#include "SFML/Graphics.hpp"

#include "Config.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"

namespace my_game {
    enum class type {
        Asteroid,
        Player,
        Bullet,
    };

    template<typename T>
    struct vec2 
    {
        T x;
        T y;
    };

    template<typename T>
    struct vec3 
    {
        T x;
        T y;
        T z;
    };

    struct AsteroidProps
    {
        int score = 0;
        int collisionR = 0;
        float rotateSpeed = 0;
        float speed = 0;
        vec2<float> dir {0., 0.};
        vec2<float> pos = {0., 0.};
        int spriteId = 0;
    };
}

class Drawer
{
public:

    Drawer(const Config& cfg);
    void pollEvent(std::vector<sf::Event>& events);
    bool isOpen();
    my_game::vec2<int> GetWindowSize();

    void InitDraw();
    void Draw(my_game::type type, my_game::vec2<float> pos, int rectId, float rotate);
    void Draw(my_game::type type, my_game::vec2<float> pos);
    void Display();

    std::function<sf::Time()> CreateSpawnTimeGetter();

    my_game::AsteroidProps GetAsteroid();

private:
    std::unique_ptr<sf::RenderWindow> _window;

    std::vector<sf::IntRect> _asterRects;
    std::vector<int> _typeOfAsterRect;
    std::unordered_map<int, my_game::AsteroidProps> _asteroids;
    Randomiser _rnd;

    sf::Time _nextAster;
    sf::Clock _spawnClock;

    std::unordered_map<my_game::type, std::shared_ptr<sf::Texture>> _textures;
    std::unordered_map<my_game::type, std::shared_ptr<sf::Sprite>> _sprites;
};