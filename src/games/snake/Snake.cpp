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
#include "../../TextSpriteHelper.hpp"

arca::Snake::Snake() : AGame<30, 30>()
{
    _tik = 0;
    _score = 0;
    _direction = GameInput::Direction::None;
    _tempDirection = GameInput::Direction::None;
    _gameOver = false;
    _sprites.push_back(std::make_unique<BackSprite>());
    _sprites.push_back(std::make_unique<PebbleSprite>());
    _sprites.push_back(std::make_unique<SnakeSprite>(16, 15, 1));
    _sprites.push_back(std::make_unique<SnakeSprite>(16, 16, 2));
    _sprites.push_back(std::make_unique<SnakeSprite>(15, 16, 3));
    _sprites.push_back(std::make_unique<SnakeSprite>(15, 15, 4));
    auto pebble = getPebble();
    while (!isPositionFree((*pebble)->x, (*pebble)->y, SNAKE_PEBBLE)) {
        _sprites.erase(pebble);
        _sprites.push_back(std::make_unique<PebbleSprite>());
        pebble = getPebble();
    }
}

arca::Snake::~Snake()
{
}

void arca::Snake::handleInput(GameInput input)
{
    if ((input.direction == GameInput::Direction::Down && _direction != GameInput::Direction::Up && _direction != GameInput::Direction::None) ||
        (input.direction == GameInput::Direction::Left && _direction != GameInput::Direction::Right) ||
        (input.direction == GameInput::Direction::Up && _direction != GameInput::Direction::Down) ||
        (input.direction == GameInput::Direction::Right && _direction != GameInput::Direction::Left))
        _tempDirection = input.direction;
}

std::vector<std::unique_ptr<arca::Sprite>>::iterator arca::Snake::getPebble()
{
    auto it = _sprites.begin();
    while (it != _sprites.end())
    {
        if ((*it)->id == SNAKE_PEBBLE)
            return it;
        it++;
    }
    return _sprites.begin();
}

void arca::Snake::update()
{
    _tik++;
    if (_tik >= 120 / (_score + 4)) {
        _tik = 0;
        _direction = _tempDirection;
        moveSnake();
    }
}

void arca::Snake::moveSnake()
{
    SpriteId id_to_find = SNAKE_HEAD;
    std::pair<unsigned, unsigned> pebble_pos;
    std::pair<unsigned, unsigned> head_pos;
    auto pebble = getPebble();
    pebble_pos = getSpritePosition(std::make_unique<Sprite>(*(*pebble)));
    auto it = std::find_if(_sprites.begin(), _sprites.end(), [id_to_find](const auto& pair) {
        return pair->id == id_to_find;
    });
    if (it != _sprites.end()) {
        head_pos = getSpritePosition(std::make_unique<Sprite>(*(*it)));
    }
    switch (_direction)
    {
    case GameInput::Direction::Up:
        if (head_pos.second <= 1) {
            gameOver();
            return;
        }
        _sprites.push_back(std::make_unique<SnakeSprite>(head_pos.first, head_pos.second - 1, 4));
        head_pos = std::make_pair(head_pos.first, head_pos.second - 1);
        
        break;
    case GameInput::Direction::Down:
        if (head_pos.second >= 28) {
            gameOver();
            return;
        }
        _sprites.push_back(std::make_unique<SnakeSprite>(head_pos.first, head_pos.second + 1, 4));
        head_pos = std::make_pair(head_pos.first, head_pos.second + 1);
        break;
    case GameInput::Direction::Left:
        if (head_pos.first <= 1) {
            gameOver();
            return;
        }
        _sprites.push_back(std::make_unique<SnakeSprite>(head_pos.first - 1, head_pos.second, 4));
        head_pos = std::make_pair(head_pos.first - 1, head_pos.second);
        break;
    case GameInput::Direction::Right:
        if (head_pos.first >= 28) {
            gameOver();
            return;
        }
        _sprites.push_back(std::make_unique<SnakeSprite>(head_pos.first + 1, head_pos.second, 4));
        head_pos = std::make_pair(head_pos.first + 1, head_pos.second);
        break;
    default:
        break;
    }
    if (head_pos.first == pebble_pos.first && head_pos.second == pebble_pos.second) {
        _score++;
        _sprites.erase(pebble);
        _sprites.push_back(std::make_unique<PebbleSprite>());

        auto pebble = getPebble();
        while (!isPositionFree((*pebble)->x, (*pebble)->y, SNAKE_PEBBLE)) {
            _sprites.erase(pebble);
            _sprites.push_back(std::make_unique<PebbleSprite>());
            pebble = getPebble();
        }

        growSnake();
    } else if (_direction != GameInput::Direction::None){
        doesntGrowSnake();
    }
    if (!isPositionFree(head_pos.first, head_pos.second, SNAKE_HEAD)) {
        gameOver();
        return;
    }
}

bool arca::Snake::isPositionFree(unsigned x, unsigned y, SpriteId id)
{
    for (auto& pair : _sprites) {
        if (pair->x == x && pair->y == y && ((pair->id == SNAKE_HEAD && id == SNAKE_PEBBLE) || pair->id == SNAKE_BODY || pair->id == SNAKE_TAIL)) {
            return false;
        }
    }
    return true;
}

void arca::Snake::growSnake()
{
    for (auto& pair : _sprites) {
        if (pair->id == SNAKE_HEAD) {
            pair->id = SNAKE_BODY;
            return;
        }
    }
}

void arca::Snake::doesntGrowSnake()
{
    auto it = _sprites.begin();
    bool found = false;

    while (it != _sprites.end()) {
        if ((*it)->id == SNAKE_TAIL) {
            it = _sprites.erase(it);
        } else if ((*it)->id == SNAKE_BODY && !found) {
            (*it)->id = SNAKE_TAIL;
            found = true;
            it++;
        } else if ((*it)->id == SNAKE_HEAD) {
            (*it)->id = SNAKE_BODY;
            return;
        } else {
            it++;
        }
    }
}

arca::SnakeSprite::SnakeSprite(unsigned new_x, unsigned new_y, unsigned num) : Sprite()
{
    _num = num;
    x = new_x;
    y = new_y;
    if (num == 4)
        id = SNAKE_HEAD;
    else if (num == 1)
        id = SNAKE_TAIL;
    else 
        id = SNAKE_BODY;
}

arca::SnakeSprite::~SnakeSprite()
{
}

const arca::GameOutput arca::Snake::nextFrame(const GameInput &input)
{
    if (input.direction != GameInput::Direction::None) {
        handleInput(input);
    }
    GameOutput output;
    if (!_gameOver) {
        update();
    }
    output.gridHeigth = 30;
    output.gridWidth = 30;
    for (auto& pair : _sprites) {
        output.sprites.push_back(*pair);
    }
    if (_gameOver) {
        std::list<Sprite> ids1 = TextSpriteHelper::stringSprites ("game over", 13.5, 10, 10);
        std::list<Sprite> ids2 = TextSpriteHelper::stringSprites ("score", 13, 11, 5);
        output.sprites.insert(output.sprites.end(), ids1.begin(), ids1.end());
        output.sprites.insert(output.sprites.end(), ids2.begin(), ids2.end());
    }
    return output;
}

const std::list<arca::SpriteId> arca::Snake::getUsedSprites() const
{
    std::list<SpriteId> ids;
    for (int i = SNAKE_HEAD; i <= SNAKE_BACK ; i++) {
        ids.push_front(SpriteId(i));
    }
    ids.push_back(CHAR_G);
    ids.push_back(CHAR_A);
    ids.push_back(CHAR_M);
    ids.push_back(CHAR_E);
    ids.push_back(CHAR_O);
    ids.push_back(CHAR_V);
    ids.push_back(CHAR_R);
    ids.push_back(CHAR_S);
    ids.push_back(CHAR_C);
    for (int i = CHAR_0; i <= CHAR_9; i++) {
        ids.push_back(SpriteId(i));
    }
    return ids;
}

extern "C" {
    uint64_t checkMagic()
    {
        return 0x12a;
    }

    std::unique_ptr<arca::IGame> getGame()
    {
        return std::make_unique<arca::Snake>();
    }
}

arca::PebbleSprite::PebbleSprite() : Sprite()
{
    clock_t t;
    t = clock();
    srand(t);
    int random_x = rand() % 28 + 1;
    int random_y = rand() % 28 + 1;
    x = random_x;
    y = random_y;
    id = SNAKE_PEBBLE;
}

arca::PebbleSprite::~PebbleSprite()
{
}

arca::BackSprite::BackSprite() : Sprite()
{
    x = 0;
    y = 0;
    id = SNAKE_BACK;
}

arca::BackSprite::~BackSprite()
{
}

unsigned arca::SnakeSprite::getNum() const
{
    return _num;
}

void arca::Snake::gameOver()
{
    SpriteId hundred = SpriteId(CHAR_0 + _score / 100);
    SpriteId ten = SpriteId(CHAR_0 + (_score % 100) / 10);
    SpriteId unit = SpriteId(CHAR_0 + _score % 10);
    _gameOver = true;
    auto it = _sprites.begin();
    while (it < _sprites.end()) {
        if ((*it)->id == SNAKE_BACK) {
            it++;
            continue;
        }
        it = _sprites.erase(it);
    }
    _sprites.push_back(std::make_unique<CharSprites>(17, 11, hundred));
    _sprites.push_back(std::make_unique<CharSprites>(17.5, 11, ten));
    _sprites.push_back(std::make_unique<CharSprites>(18, 11, unit));
    
}

arca::CharSprites::CharSprites(double x, double y, SpriteId type) : Sprite()
{
    this->x = x;
    this->y = y;
    id = type;
}

arca::CharSprites::~CharSprites()
{
}