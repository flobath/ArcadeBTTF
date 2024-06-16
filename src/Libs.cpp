/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** Libs
*/

#include "Libs.hpp"
#include "IGame.hpp"
#include <dlfcn.h>
#include <iostream>
#include <dirent.h>
#include <vector>

arc::Libs::Libs()
{
    _checkMagicNumber = []() -> u_int64_t {
        return 0;
    };
    load_libs("./src/lib");
}

arc::Libs::~Libs()
{
}


std::unique_ptr<arc::IGame> arc::Libs::open_game_lib(const std::string &lib_path)
{
    void *handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!handle)
        throw arc::Libs::LibsException("No such file");
    void *tmp2 = dlsym(handle, "magicNumber");
    if (!tmp2)
        throw arc::Libs::LibsException("Library open failed");
    auto magicNumber = reinterpret_cast<u_int64_t(*)()>(tmp2);
    _checkMagicNumber = magicNumber;
    // if (!is_game_lib())
    //     throw arc::Libs::LibsException("Library is not a game library");
    void *tmp = dlsym(handle, "getDisplay");
    if (!tmp)
        throw arc::Libs::LibsException("Library open failed");
    auto entryPoint = reinterpret_cast<std::unique_ptr<IGame>(*)()>(tmp);
    return(entryPoint());
}

std::unique_ptr<arc::IGraphical> arc::Libs::open_graphic_lib(const std::string &lib_path)
{
    void *handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!handle)
        throw arc::Libs::LibsException("No such file");
    void *tmp2 = dlsym(handle, "checkMagic");
    if (!tmp2)
        throw arc::Libs::LibsException("Library open failed");
    auto magicNumber = reinterpret_cast<u_int64_t(*)()>(tmp2);
    _checkMagicNumber = magicNumber;
    if (!is_graphic_lib())
        throw arc::Libs::LibsException("Library is not a graphic library");
    void *tmp = dlsym(handle, "getDisplay");
    if (!tmp)
        throw arc::Libs::LibsException("Library open failed");
    auto entryPoint = reinterpret_cast<std::unique_ptr<IGraphical>(*)()>(tmp);
    return(entryPoint());
}

bool arc::Libs::is_game_lib()
{
    return _checkMagicNumber && _checkMagicNumber() == 0x12a;
}

bool arc::Libs::is_graphic_lib()
{
    return _checkMagicNumber && _checkMagicNumber() == 0x22a;
}

void arc::Libs::load_libs(const std::string &directory)
{
    DIR *dir = opendir(directory.c_str());
    if (!dir) {
        throw LibsException("Failed to open directory: " + directory);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) { // Regular file
            std::string filename = entry->d_name;
            if (filename.size() >= 3 && filename.substr(filename.size() - 3) == ".so") {
                std::string filepath = directory + "/" + filename;
                try {
                    auto game_lib = open_game_lib(filepath);
                    _games.push_back(filepath);
                } catch (const LibsException &) {
                    try {
                        auto graphic_lib = open_graphic_lib(filepath);
                        _libs.push_back(filepath);
                    } catch (const LibsException &) {
                    }
                }
            }
        }
    }

    closedir(dir);
}