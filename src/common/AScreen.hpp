/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** AScreen
*/

#ifndef ASCREEN_HPP_
#define ASCREEN_HPP_

#include <vector>
#include "IScreen.hpp"

namespace arc
{
    class AScreen : public IScreen
    {
    public:
        AScreen();
        ~AScreen();

        void setSize(unsigned int width, unsigned int height) override;
        std::pair<unsigned int, unsigned int> getSize() const override;
        void setTile(unsigned int x, unsigned int y, const Tile &tile) override;
        const Tile &getTile(unsigned int x, unsigned int y) const override;
    protected:
        std::pair<unsigned int, unsigned int> _size;
        std::vector<std::vector<Tile>> _tiles;
    };
} // namespace arc

#endif /* !ASCREEN_HPP_ */
