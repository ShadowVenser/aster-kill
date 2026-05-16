#include "Timer.h"

Timer::Timer(std::function<sf::Time()> getter): _getTime(getter) 
{
    _currentWaitFor = _getTime();
    _timer.restart();
}

bool Timer::isEvent() 
{
    if (!_timer.isRunning())
        _timer.start();
    if (_currentWaitFor > _timer.getElapsedTime())
        return false;
    _currentWaitFor = _getTime();
    _timer.restart();
    return true;
}

void Timer::pause()
{
    if (_timer.isRunning())
        _timer.stop();
}