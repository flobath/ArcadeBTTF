/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** AScreen
*/

#include "AScreen.hpp"

arc::AScreen::AScreen()
{
}

arc::AScreen::~AScreen()
{
}

void arc::AScreen::setSize(unsigned int width, unsigned int height)
{
    _size = std::make_pair(width, height);
    _tiles.resize(height);
    for (unsigned int i = 0; i < height; i++)
        _tiles[i].resize(width);
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
