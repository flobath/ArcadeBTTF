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
#include <iostream>
#include "Snake.hpp"

arc::Snake::Snake() : AGame()
{
    _tik = 0;
    _score = 0;
    randomPebble();
}

arc::Snake::~Snake()
{
}

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
    if (events.size() > 0) {
        if ((events.front() == Event::EventDown && _direction != Event::EventUp) ||
            (events.front() == Event::EventLeft && _direction != Event::EventRight) ||
            (events.front() == Event::EventUp && _direction != Event::EventDown) ||
            (events.front() == Event::EventRight && _direction != Event::EventLeft))
            _tempDirection = events.front();
    }
    _tik += static_cast<unsigned>(elapsed);
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
    for(auto& pair : _sprites) {
        IScreen::Tile tile;
        switch (pair.id)
        {
        case SNAKE_HEAD:
            tile.textCharacters = std::make_pair('O', ' ');
            break;
        case SNAKE_BODY:
            tile.textCharacters = std::make_pair('o', ' ');
            break;
        case SNAKE_PEBBLE:
            tile.textCharacters = std::make_pair('X', ' ');
            break;
        case SNAKE_TAIL:
            tile.textCharacters = std::make_pair('o', ' ');
            break;
        }
        screen.setTile(pair.x, pair.y, tile);
    }
}
