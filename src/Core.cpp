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


arc::Core::Core(const std::string &lib_path)
{
    _libLoader = std::make_unique<Libs>();
    _lib = _libLoader->open_graphic_lib(lib_path);
    get_libs();
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