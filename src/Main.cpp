/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** Main
*/

#include <iostream>
#include <exception>
#include <cstring>
#include <dlfcn.h>
#include "Core.hpp"

int main(int argc, char **argv)
{
    if (argc != 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        std::cerr
            << "Usage: " << argv[0]
            << "path/to/graphic_lib.so" << std::endl;
        return argc != 2 ? 84 : 0;
    }
    try {
        arc::Core core(argv[1]);
        core.run();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Core exited with an exception: '"
            << e.what() << "'" << std::endl;
        return 84;
    }
}
