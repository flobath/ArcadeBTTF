/*
** EPITECH PROJECT, 2024
** B-OOP-400-NAN-4-1-arcade-florian.gaudin
** File description:
** snake
*/

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <memory>
#include <random>
#include "Snake.hpp"

arc::Snake::Snake() : AGame()
{
    _tik = 0;
    _score = 0;
    _gameOver = false;
    auto pebble = getPebble();
    while (!isPositionFree(pebble->x, pebble->y, SNAKE_PEBBLE)) {
        _sprites.erase(pebble);
        pebble = getPebble();
    }
}

arc::Snake::~Snake()
{
}

// void arc::Snake::handleInput(GameInput input)
// {
//     if ((input.direction == Event::Down && _direction != Event::Up && _direction != Event::None) ||
//         (input.direction == Event::Left && _direction != Event::Right) ||
//         (input.direction == Event::Up && _direction != Event::Down) ||
//         (input.direction == Event::Right && _direction != Event::Left))
//         _tempDirection = input.direction;
// } TODO

std::vector<arc::Snake::Sprite>::iterator arc::Snake::getPebble()
{
    auto it = _sprites.begin();
    while (it != _sprites.end())
    {
        if ((*it).id == SNAKE_PEBBLE)
            return it;
        it++;
    }
    return _sprites.begin();
}

void arc::Snake::update(float elapsed, const std::list<Event> &events)
{
    (void)elapsed;
    (void)events;
    _tik++;
    if (_tik >= 120 / (_score + 4)) {
        _tik = 0;
        _direction = _tempDirection;
        moveSnake();
    }
}

void arc::Snake::moveSnake()
{
    SpriteId id_to_find = SNAKE_HEAD;
    std::pair<unsigned, unsigned> pebble_pos;
    std::pair<unsigned, unsigned> head_pos;
    auto pebble = getPebble();
    pebble_pos = getSpritePosition(pebble);
    auto it = std::find_if(_sprites.begin(), _sprites.end(), [id_to_find](const Sprite &sprite) {
        return sprite.id == id_to_find;
    });
    if (it != _sprites.end()) {
        head_pos = getSpritePosition(it);
    }
    switch (_direction)
    {
    case Event::EventUp:
        if (head_pos.second <= 1) {
            // gameOver();
            return;
        }
        _sprites.push_back(Sprite(head_pos.first, head_pos.second - 1, SNAKE_HEAD));
        head_pos = std::make_pair(head_pos.first, head_pos.second - 1);
        
        break;
    case Event::EventDown:
        if (head_pos.second >= 28) {
            // gameOver();
            return;
        }
        _sprites.push_back(Sprite(head_pos.first, head_pos.second + 1, SNAKE_HEAD));
        head_pos = std::make_pair(head_pos.first, head_pos.second + 1);
        break;
    case Event::EventLeft:
        if (head_pos.first <= 1) {
            // gameOver();
            return;
        }
        _sprites.push_back(Sprite(head_pos.first - 1, head_pos.second, SNAKE_HEAD));
        head_pos = std::make_pair(head_pos.first - 1, head_pos.second);
        break;
    case Event::EventRight:
        if (head_pos.first >= 28) {
            // gameOver();
            return;
        }
        _sprites.push_back(Sprite(head_pos.first + 1, head_pos.second, SNAKE_HEAD));
        head_pos = std::make_pair(head_pos.first + 1, head_pos.second);
        break;
    default:
        break;
    }
    if (head_pos.first == pebble_pos.first && head_pos.second == pebble_pos.second) {
        _score++;
        _sprites.erase(pebble);
        randomPebble();

        auto pebble = getPebble();
        while (!isPositionFree(pebble->x, pebble->y, SNAKE_PEBBLE)) {
            _sprites.erase(pebble);
            randomPebble();
            pebble = getPebble();
        }

        growSnake();
    } else if (_direction){
        doesntGrowSnake();
    }
    if (!isPositionFree(head_pos.first, head_pos.second, SNAKE_HEAD)) {
        // gameOver();
        return;
    }
}

bool arc::Snake::isPositionFree(unsigned x, unsigned y, SpriteId id)
{
    for (auto& pair : _sprites) {
        if (pair.x == x && pair.y == y && ((pair.id == SNAKE_HEAD && id == SNAKE_PEBBLE) || pair.id == SNAKE_BODY || pair.id == SNAKE_TAIL)) {
            return false;
        }
    }
    return true;
}

void arc::Snake::growSnake()
{
    for (auto& pair : _sprites) {
        if (pair.id == SNAKE_HEAD) {
            pair.id = SNAKE_BODY;
            return;
        }
    }
}

void arc::Snake::doesntGrowSnake()
{
    auto it = _sprites.begin();
    bool found = false;

    while (it != _sprites.end()) {
        if (it->id == SNAKE_TAIL) {
            it = _sprites.erase(it);
        } else if (it->id == SNAKE_BODY && !found) {
            it->id = SNAKE_TAIL;
            found = true;
            it++;
        } else if (it->id == SNAKE_HEAD) {
            it->id = SNAKE_BODY;
            return;
        } else {
            it++;
        }
    }
}
// const arc::GameOutput arc::Snake::nextFrame(const GameInput &input)
// {
//     if (input.direction != Event::None) {
//         handleInput(input);
//     }
//     GameOutput output;
//     if (!_gameOver) {
//         update();
//     }
//     output.gridHeigth = 30;
//     output.gridWidth = 30;
//     for (auto& pair : _sprites) {
//         output.sprites.push_back(*pair);
//     }
//     if (_gameOver) {
//         std::list<Sprite> ids1 = TextSpriteHelper::stringSprites ("game over", 13.5, 10, 10);
//         std::list<Sprite> ids2 = TextSpriteHelper::stringSprites ("score", 13, 11, 5);
//         output.sprites.insert(output.sprites.end(), ids1.begin(), ids1.end());
//         output.sprites.insert(output.sprites.end(), ids2.begin(), ids2.end());
//     }
//     return output;
// }

extern "C" {
    uint64_t checkMagic()
    {
        return 0x12a;
    }

    std::unique_ptr<arc::IGame> getGame()
    {
        return std::make_unique<arc::Snake>();
    }
}

void arc::Snake::randomPebble()
{
    bool found = false;
    Sprite pebble(0, 0, SNAKE_PEBBLE);

    while (!found) {
        pebble.x = rand() % 28 + 1;
        pebble.y = rand() % 28 + 1;
        if (isPositionFree(pebble.x, pebble.y, SNAKE_PEBBLE)) {
            found = true;
        }
    }
}

arc::Snake::Sprite::Sprite(unsigned x, unsigned y, SpriteId id)
{
    this->x = x;
    this->y = y;
    this->id = id;
}

arc::Snake::Sprite::~Sprite()
{
}

std::pair<unsigned, unsigned> arc::Snake::getSpritePosition(std::vector<Sprite>::iterator sprite)
{
    return std::make_pair(sprite->x, sprite->y);
}

void arc::Snake::draw(arc::IScreen &screen)
{
}