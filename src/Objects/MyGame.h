#pragma once

#include "SFML/Graphics.hpp"

#include "../Ecs/World/World.h"

namespace my_game 
{
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

    struct GuiBinder 
    {
        World* world;
        bool* isGuiVisible;
        sf::RenderWindow* renderer;

        float* meanTime;
        float* stdTime;

        bool* spawner;
    };
};