/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** Core
*/

#include "Core.hpp"
#include "IGraphical.hpp"
#include <string>
#include <stdexcept>
#include <dlfcn.h>
#include <memory>
#include <iostream>


arc::Core::Core(const std::string &lib_path) : _libLoader(std::make_unique<arc::Libs>()), _lib(nullptr), _game(nullptr),
    _screen(arc::AScreen()), _events()
{
    _lib = _libLoader->open_graphic_lib(lib_path);
    _game = _libLoader->open_game_lib("./src/games/snake/arcade_snake.so");
    get_libs();
    clock_t start;
    clock_t end;
    float elapsed;
    start = clock();
    while (true) {
        end = clock();
        elapsed = ((float)end - start) / (CLOCKS_PER_SEC * 1000);
        _game->update(elapsed, _events);
        _game->draw(_screen);
        _events.clear();
        _events = _lib->events();
        _lib->draw(_screen);
        for (auto &event : _events) {
            if (event == arc::Event::EventExit) {
                return;
            } else if (event == arc::Event::EventNextGame) {
                next_game();
            } else if (event == arc::Event::EventPreviousGraphical) {
                prev_graphical();
            } else if (event == arc::Event::EventNextGraphical) {
                next_game();
            } else if (event == arc::Event::EventPreviousGame) {
                prev_game();
            } else if (event == arc::Event::EventRestart) {
                _game = _libLoader->open_game_lib(_games[_games.size() - 1]);
                _lib = _libLoader->open_graphic_lib(lib_path);
            }
        }
        if (elapsed >= 1) {
            start = clock();
        }
    }
}

arc::Core::~Core()
{
}

void arc::Core::run()
{
}

void arc::Core::get_libs()
{
    _libs = _libLoader->get_libs();
    _games = _libLoader->get_games();
}

void arc::Core::next_graphical()
{
    _lib = _libLoader->open_graphic_lib(_libs[0]);
    _libs.push_back(_libs[0]);
    _libs.erase(_libs.begin());
}

void arc::Core::next_game()
{
    _game = _libLoader->open_game_lib(_games[0]);
    _games.push_back(_games[0]);
    _games.erase(_games.begin());
}

void arc::Core::prev_graphical()
{
    _libs.insert(_libs.begin(), _libs[_libs.size() - 1]);
    _libs.pop_back();
    _lib = _libLoader->open_graphic_lib(_libs[_libs.size() - 1]);
}

void arc::Core::prev_game()
{
    _games.insert(_games.begin(), _games[_games.size() - 1]);
    _games.pop_back();
    _game = _libLoader->open_game_lib(_games[_games.size() - 1]);
}
