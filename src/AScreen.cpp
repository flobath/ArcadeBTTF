/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** AScreen
*/

#include "AScreen.hpp"

arc::AScreen::AScreen() : _size(0, 0)
{
}

arc::AScreen::~AScreen()
{
}

void arc::AScreen::setSize(unsigned int width, unsigned int height)
{
    _tiles.resize(height);
    for (auto &line : _tiles)
        line.resize(width);
    _size = std::make_pair(width, height);
}

std::pair<unsigned int, unsigned int> arc::AScreen::getSize() const
{
    return _size;
}

void arc::AScreen::setTile(unsigned int x, unsigned int y, const Tile &tile)
{
    if (x >= _size.first || y >= _size.second)
        return;
    _tiles[y][x] = tile;
}

const arc::IScreen::Tile &arc::AScreen::getTile(unsigned int x, unsigned int y) const
{
    if (x >= _size.first || y >= _size.second)
        return _tiles[0][0];
    return _tiles[y][x];
}
