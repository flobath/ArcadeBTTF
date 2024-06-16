/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** Ncurse
*/

#include "Ncurse.hpp"
#include <ncurses.h>
#include <memory>
#include <iostream>
#include <unistd.h>

arc::Ncurse::Ncurse()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

arc::Ncurse::~Ncurse()
{
    endwin();
}

void arc::Ncurse::draw(const IScreen &screen) {
    std::pair<unsigned int, unsigned int> size = screen.getSize();


    for (unsigned int y = 0; y < size.second; y++) {
        for (unsigned int x = 0; x < size.first; x++) {
            const IScreen::Tile &tile = screen.getTile(x, y);
            std::string filepath = "assets/ncurse/" + tile.texturePath;
            init_pair(1, tile.textColor, tile.textBackground);
            char display_char = '?';
            int color_pair = 1;

            if (tile.texturePath != "") {
                display_char = ' ';
                color_pair = 1;
            } else {
                display_char = tile.textCharacters.first;
                color_pair = 1;
            }
            attron(COLOR_PAIR(color_pair));
            mvaddch(y, x, display_char);
            attroff(COLOR_PAIR(color_pair));
        }
    }

    refresh();
    getch();
}

extern "C" {
    uint64_t checkMagic()
    {
        return 0x22a;
    }

    std::unique_ptr<arc::IGraphical> createGraphical()
    {
        return std::make_unique<arc::Ncurse>();
    }
}