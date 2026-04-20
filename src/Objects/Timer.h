#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

class Timer {
public:
    Timer(std::function<sf::Time()> getter);
    bool isEvent();
private:
    std::function<sf::Time()> _getTime;
    sf::Time _currentWaitFor;
    sf::Clock _timer;
};
