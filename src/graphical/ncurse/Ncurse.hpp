/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** Ncurse
*/

#ifndef NCURSE_HPP_
#define NCURSE_HPP_

#include <ncurses.h>
#include "AGraphical.hpp"

namespace arc
{
    class Ncurse : public AGraphical
    {
    public:
        Ncurse();
        ~Ncurse();

        void draw(const IScreen &screen) override;
        std::list<Event> events() override;
    };
} // namespace arc


#endif /* !NCURSE_HPP_ */
