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
    _noMove = true;
    _sprites.push_back(Sprite(15, 17, SNAKE_TAIL));
    _sprites.push_back(Sprite(15, 16, SNAKE_BODY));
    _sprites.push_back(Sprite(15, 15, SNAKE_HEAD));
    for (unsigned i = 0; i < 30; i++) {
        _sprites.push_back(Sprite(i, 0, WALLS));
        _sprites.push_back(Sprite(i, 29, WALLS));
        _sprites.push_back(Sprite(0, i, WALLS));
        _sprites.push_back(Sprite(29, i, WALLS));
    }
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
    for (auto &event : events) {
        if ((event == Event::EventDown && _direction != Event::EventUp) ||
            (event == Event::EventLeft && _direction != Event::EventRight) ||
            (event == Event::EventUp && _direction != Event::EventDown) ||
            (event == Event::EventRight && _direction != Event::EventLeft)) {
                _tempDirection = events.front();
                _noMove = false;
            }
    }
    _tik ++;
    if (elapsed >= 0.005 / (_score + 4)) {
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
    if (_noMove) {
        return;
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
        it->id = SNAKE_BODY;
        break;
    case Event::EventDown:
        if (head_pos.second >= 28) {
            // gameOver();
            return;
        }
        _sprites.push_back(Sprite(head_pos.first, head_pos.second + 1, SNAKE_HEAD));
        head_pos = std::make_pair(head_pos.first, head_pos.second + 1);
        it->id = SNAKE_BODY;
        break;
    case Event::EventLeft:
        if (head_pos.first <= 1) {
            // gameOver();
            return;
        }
        _sprites.push_back(Sprite(head_pos.first - 1, head_pos.second, SNAKE_HEAD));
        head_pos = std::make_pair(head_pos.first - 1, head_pos.second);
        it->id = SNAKE_BODY;
        break;
    case Event::EventRight:
        if (head_pos.first >= 28) {
            // gameOver();
            return;
        }
        _sprites.push_back(Sprite(head_pos.first + 1, head_pos.second, SNAKE_HEAD));
        head_pos = std::make_pair(head_pos.first + 1, head_pos.second);
        it->id = SNAKE_BODY;
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
    // for (auto& pair : _sprites) {
    //     if (pair.id == SNAKE_HEAD) {
    //         pair.id = SNAKE_BODY;
    //         return;
    //     }
    // }
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
        // } else if (it->id == SNAKE_HEAD) {
        //     it->id = SNAKE_BODY;
        //     return;
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
    _sprites.push_back(pebble);
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
    screen.setSize(30, 30);
    for (unsigned i = 0; i < 30; i++) {
        for (unsigned j = 0; j < 30; j++) {
            IScreen::Tile tile;
            tile.textCharacters = std::make_pair(' ', ' ');
            screen.setTile(i, j, tile);
        }
    }
    for(auto& pair : _sprites) {
        IScreen::Tile tile;
        switch (pair.id)
        {
        case SNAKE_HEAD:
            tile.textCharacters = std::make_pair('M', ' ');
            break;
        case SNAKE_BODY:
            tile.textCharacters = std::make_pair('o', ' ');
            break;
        case SNAKE_PEBBLE:
            tile.textCharacters = std::make_pair('X', ' ');
            break;
        case SNAKE_TAIL:
            tile.textCharacters = std::make_pair('V', ' ');
            break;
        case WALLS:
            tile.textCharacters = std::make_pair('|', ' ');
            break;
        case FLOOR_ROOF:
            tile.textCharacters = std::make_pair('-', ' ');
            break;
        }
        screen.setTile(pair.x, pair.y, tile);
    }
}
