/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../common/IGraphical.hpp"
#include "../common/IGame.hpp"
#include "../common/IScreen.hpp"
#include "Libs.hpp"
#include <string>
#include <memory>
#include <vector>

namespace arc
{
    class Core
    {
    public:
        Core(const std::string &lib_path);
        ~Core();

        void get_libs();
        void run();
    protected:
        std::unique_ptr<IGraphical> _lib;
        std::unique_ptr<IGame> _game;
        std::unique_ptr<IScreen> _screen;
        std::vector<std::string> _games;
        std::vector<std::string> _libs;
        std::unique_ptr<Libs> _libLoader;
    };
} // namespace arc


#endif /* !CORE_HPP_ */
