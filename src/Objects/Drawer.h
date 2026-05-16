#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "MyGame.h"
#include "Randomiser.h"

#include "Config.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"

class Drawer
{
public:

    Drawer(const Config& cfg);
    void pollEvent(std::vector<sf::Event>& events, my_game::vec2<bool>& isPressed);
    bool isOpen();

    my_game::vec2<int> GetWindowSize();
    my_game::vec2<int> GetSpriteSize(my_game::type id);

    void InitDraw();
    void Draw(my_game::type type, my_game::vec2<float> pos, int rectId, float rotate);
    void Draw(my_game::type type, my_game::vec2<float> pos);
    void Display();

    void SetScore(int val);

    void DrawGameOver();

    std::function<sf::Time()> CreateSpawnTimeGetter();

    my_game::AsteroidProps GetAsteroid();

    void BindGui(my_game::GuiBinder& binder);

private:
    int _score = 0;
    std::unique_ptr<sf::RenderWindow> _window;

    std::vector<sf::IntRect> _asterRects;
    std::vector<int> _typeOfAsterRect;
    std::unordered_map<int, my_game::AsteroidProps> _asteroids;
    Randomiser _rnd;

    std::unordered_map<my_game::type, std::shared_ptr<sf::Texture>> _textures;
    std::unordered_map<my_game::type, std::shared_ptr<sf::Sprite>> _sprites;

    sf::Font _font;
    std::shared_ptr<sf::Text> _scoreText;
    std::shared_ptr<sf::Text> _gameOverText;
};