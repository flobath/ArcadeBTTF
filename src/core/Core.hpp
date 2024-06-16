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
#include "AScreen.hpp"
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

        void next_graphical();
        void next_game();
        void prev_graphical();
        void prev_game();

        void get_libs();
        void run();
    protected:
        std::unique_ptr<Libs> _libLoader;
        std::unique_ptr<IGraphical> _lib;
        std::unique_ptr<IGame> _game;
        AScreen _screen;
        std::vector<std::string> _games;
        std::vector<std::string> _libs;
        std::list<arc::Event> _events;
    };
} // namespace arc


#endif /* !CORE_HPP_ */
