#pragma once

#include <concepts>
#include <random>
#include <type_traits>
#include "Config.h"
#include "SFML/System/Vector2.hpp"

class Randomiser
{
public:
    Randomiser(const Config& cfg);

    float GetSrcPosition();
    float GetDstPosition();
    float GetSpeed();
    float GetRotate();
    int GetSprite();
    float GetSpawnTime();

private:
    unsigned int _seed;
    std::mt19937 _gen;
 
    // ASTEROID

    // std::normal_distribution<float> dst;
    // std::uniform_real_distribution<float> src;
    // std::normal_distribution<float> speed;
    // std::uniform_real_distribution<float> rotate;
    // std::uniform_int_distribution<int> sprite;
    // std::normal_distribution<float> spawn_time;

    sf::Vector2<float> _dstMS;
    sf::Vector2<float> _dstMM;
    sf::Vector2<float> _src;
    sf::Vector2<float> _speedMS;
    sf::Vector2<float> _speedMM;
    sf::Vector2<float> _rotate;
    sf::Vector2<int> _sprite;
    sf::Vector2<float> _spawn_time;


    template<typename _In = float, std::floating_point _Out = float>
    requires std::is_arithmetic_v<_In>
    sf::Vector2<_Out> _GetMeanStd(_In min, _In max)
    {
        sf::Vector2<_Out> meanStd;
        meanStd.x = (max + min) / 2.0;
        meanStd.y = (std::abs(max) + std::abs(min)) / 2.5;
        return meanStd;
    }
};