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
            init_pair(1, tile.textColor, tile.textBackground);
            char display_char = tile.textCharacters.first;
            int color_pair = 1;

            attron(COLOR_PAIR(color_pair));
            mvaddch(y, x * 2, display_char);
            attroff(COLOR_PAIR(color_pair));
        }
    }
    refresh();
    getch();
}

std::list<arc::Event> arc::Ncurse::events() {
    std::list<Event> events;
    int key;
    nodelay(stdscr, TRUE);

    while ((key = getch()) != ERR) {
        switch (key) {
            case KEY_UP:
                events.push_back(Event::EventUp);
                break;
            case KEY_DOWN:
                events.push_back(Event::EventDown);
                break;
            case KEY_LEFT:
                events.push_back(Event::EventLeft);
                break;
            case KEY_RIGHT:
                events.push_back(Event::EventRight);
                break;
            case 27:
                events.push_back(Event::EventExit);
                break;
            case 32:
                events.push_back(Event::EventAction);
                break;
            default:
                break;
        }
    }
    return events;
}

extern "C" {
    uint64_t checkMagic()
    {
        return 0x22a;
    }

    std::unique_ptr<arc::IGraphical> getDisplay()
    {
        return std::make_unique<arc::Ncurse>();
    }
}
