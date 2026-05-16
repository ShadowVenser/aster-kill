#include "Drawer.h"
#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/Angle.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "imgui-SFML.h"

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

    _window->setKeyRepeatEnabled(false);

    if (!ImGui::SFML::Init(*_window))
        throw std::runtime_error("IMGUI FAILED!!!");

    // ---------- ASTEROIDS INIT ----------

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
                .collisionR=asteroid.at("collision").get<int>()
            }
        });
    }

    // ---------- PLAYER INIT ----------
    
    _textures.insert({
        my_game::type::Player, 
        std::make_shared<sf::Texture>(
            cfg.cfg().at("player").at("sprite").get<std::string>()
        )}
    );

    _sprites.insert({
        my_game::type::Player,
        std::make_shared<sf::Sprite>(*_textures[my_game::type::Player])
    });

    // ---------- BULLET INIT ----------
    
    _textures.insert({
        my_game::type::Bullet, 
        std::make_shared<sf::Texture>(
            cfg.cfg().at("bullet").at("sprite").get<std::string>()
        )}
    );

    _sprites.insert({
        my_game::type::Bullet,
        std::make_shared<sf::Sprite>(*_textures[my_game::type::Bullet])
    });

    // ---------- LABELS INIT ----------

    if (_font.openFromFile(cfg.cfg().at("font").at("path").get<std::string>()))
    {
        _gameOverText = std::make_shared<sf::Text>(_font, "", cfg.cfg().at("font").at("size").get<int>());
        _scoreText = std::make_shared<sf::Text>(_font, "Score: 0", cfg.cfg().at("font").at("size").get<int>());
    }
    
    _scoreText->setPosition({
        0.f,
        _window->getSize().y - _scoreText->getGlobalBounds().size.y
    });
}

void Drawer::pollEvent(std::vector<sf::Event>& events, my_game::vec2<bool>& isPressed)
{
    while (const std::optional event = _window->pollEvent())
    {
        ImGui::SFML::ProcessEvent(*_window, *event);

        if (event->is<sf::Event::Closed>())
        {
            _window->close();
        }
        else if (auto kpe = event->getIf<sf::Event::KeyPressed>(); kpe)
        {
            events.push_back(*kpe);
        }
    }
    isPressed.x = false 
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    isPressed.y = false 
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
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
    _window->draw(*_scoreText);
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
        if (_gameOverText)
        {
            _gameOverText->setString("Game Over\nScore: " + std::to_string(_score));
            _gameOverText->setPosition({
                (_window->getSize().x - _gameOverText->getGlobalBounds().size.x) / 2,
                (_window->getSize().y - _gameOverText->getGlobalBounds().size.y) / 2
            });
        }
        isFirst = false;
    }
    _window->clear();
    if (_gameOverText)
    {
        _window->draw(*_gameOverText);
    }
    _window->display();
}

void Drawer::SetScore(int val)
{
    _score = val;
    _scoreText->setString("Score: " + std::to_string(val));
}

my_game::vec2<int> Drawer::GetSpriteSize(my_game::type id)
{
    auto& rect = _sprites[id]->getTextureRect();
    return {
        .x = rect.size.x,
        .y = rect.size.y
    };
}

void Drawer::BindGui(my_game::GuiBinder& binder)
{
    binder.renderer = &(*_window);
    _rnd.BindGui(binder);
}
