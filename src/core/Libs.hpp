/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** Libs
*/

#ifndef LIBS_HPP_
#define LIBS_HPP_

#include "IGame.hpp"
#include "IGraphical.hpp"
#include <string>
#include <memory>
#include <functional>
#include <vector>

namespace arc
{
    class Libs
    {
    private:
    public:
        class LibsException : public std::exception
        {
        public:
            LibsException(const std::string &message) : _message(message) {}
            const char *what() const noexcept override { return _message.c_str(); }
        protected:
            std::string _message;
        };
        Libs();
        ~Libs();

        std::unique_ptr<IGame> open_game_lib(const std::string &lib_path);
        std::unique_ptr<IGraphical> open_graphic_lib(const std::string &lib_path);
        bool is_game_lib();
        bool is_graphic_lib();
        std::vector<std::string> get_libs() { return _libs; }
        std::vector<std::string> get_games() { return _games; }
        void load_libs(const std::string &directory);

        protected:
            std::function<u_int64_t(void)> _checkMagicNumber;
            std::vector<std::string> _libs;
            std::vector<std::string> _games;
    };
    
} // namespace arc


#endif /* !LIBS_HPP_ */
