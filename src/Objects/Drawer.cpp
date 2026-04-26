#include "Drawer.h"
#include <cmath>
#include <memory>
#include <string>
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/Angle.hpp"
#include "SFML/System/Time.hpp"

Drawer::Drawer(const Config& cfg):
    _rnd(cfg)
{
    auto w = cfg.cfg().at("window").at("width").get<uint32_t>();
    auto h = cfg.cfg().at("window").at("height").get<uint32_t>();
    auto name = cfg.cfg().at("name").get<std::string>();
    auto ver = cfg.cfg().at("version").get<std::string>();

    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode({w, h}), name + "\t" + ver);
    _window->setFramerateLimit(60);
    _window->setVerticalSyncEnabled(true);

    _nextAster = sf::milliseconds(_rnd.GetSpawnTime());
    _spawnClock.restart();

    _textures.insert({
        my_game::type::Asteroid, 
        std::make_shared<sf::Texture>(
            cfg.cfg().at("asteroid").at("texture").at("path").get<std::string>()
        )}
    );

    _sprites.insert({
        my_game::type::Asteroid,
        std::make_shared<sf::Sprite>(*_textures[my_game::type::Asteroid])
    });

    auto count = cfg.cfg().at("asteroid").at("texture").at("sprite_count").get<int>();
    int x = _textures[my_game::type::Asteroid]->getSize().x / count;
    int y = _textures[my_game::type::Asteroid]->getSize().y;

    _sprites[my_game::type::Asteroid]->setOrigin({x  / 2.f, y / 2.f});

    for (int rect = 0; rect < count; ++rect)
    {
        _asterRects.push_back({{x * rect, 0}, {x, y}});
        _typeOfAsterRect.push_back(cfg.cfg().at("asteroid").at("texture").at("types").at(rect).get<int>());
    }

    for (auto asteroid: cfg.cfg().at("asteroid").at("types"))
    {
        _asteroids.insert({
            asteroid.at("id").get<int>(), 
            {
                .score=asteroid.at("score").get<int>(),
                .collisionR=asteroid.at("score").get<int>()
            }
        });
    }

    if (_font.openFromFile(cfg.cfg().at("font").at("path").get<std::string>()))
    {
        _gameOver = std::make_shared<sf::Text>(_font, "", cfg.cfg().at("font").at("size").get<int>());
    }
}

void Drawer::pollEvent(std::vector<sf::Event>& events)
{
    while (const std::optional event = _window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            _window->close();
        }
        else if (auto kpe = event->getIf<sf::Event::KeyPressed>(); kpe)
        {
            events.push_back(*kpe);
        }
    }
}

bool Drawer::isOpen()
{
    return _window->isOpen();
}

void Drawer::Draw(my_game::type type, my_game::vec2<float> pos)
{
    _sprites[type]->setPosition({pos.x, pos.y});
    _window->draw(*_sprites[type]);
}

void Drawer::Draw(my_game::type type, my_game::vec2<float> pos, int rectId, float rotate)
{
    _sprites[type]->setRotation(sf::degrees(rotate));
    _sprites[type]->setTextureRect(_asterRects[rectId]);
    Draw(type, pos);
}

my_game::AsteroidProps Drawer::GetAsteroid()
{
    auto sId = _rnd.GetSprite();
    my_game::AsteroidProps aster{_asteroids[_typeOfAsterRect[sId]]};
    aster.rotateSpeed = _rnd.GetRotate();
    aster.pos.x = _rnd.GetSrcPosition() * _window->getSize().x;
    aster.pos.y = - (_sprites[my_game::type::Asteroid]->getTextureRect().size.y / 2.f);
    my_game::vec2<float> dst {
        _rnd.GetDstPosition() * _window->getSize().x,
        _window->getSize().y + _sprites[my_game::type::Asteroid]->getTextureRect().size.y / 2.f
    };
    dst.x -= aster.pos.x;
    dst.y -= aster.pos.y;
    auto z = std::sqrt(dst.x * dst.x + dst.y + dst.y);
    dst.x /= z;
    dst.y /= z;
    aster.speed = _rnd.GetSpeed();
    aster.dir = {dst.x, dst.y};
    aster.spriteId = sId;
    return aster;
}

std::function<sf::Time()> Drawer::CreateSpawnTimeGetter()
{
    return [rnd = &_rnd](){return sf::milliseconds(rnd->GetSpawnTime());};
}

void Drawer::InitDraw()
{
    _window->clear();
}

void Drawer::Display()
{
    _window->display();
}

my_game::vec2<int> Drawer::GetWindowSize()
{
    auto size = _window->getSize();
    return {(int)size.x, (int)size.y};
}

void Drawer::DrawGameOver()
{
    static bool isFirst = true;
    
    if (isFirst)
    {
        if (_gameOver)
        {
            _gameOver->setString("Game Over\nScore: " + std::to_string(_score));
            _gameOver->setPosition({
                (_window->getSize().x - _gameOver->getGlobalBounds().size.x) / 2,
                (_window->getSize().y - _gameOver->getGlobalBounds().size.y) / 2
            });
        }
        isFirst = false;
    }
    _window->clear();
    if (_gameOver)
    {
        _window->draw(*_gameOver);
    }
    _window->display();
}
