/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** AGraphical
*/

#ifndef AGRAPHICAL_HPP_
#define AGRAPHICAL_HPP_

#include "../../common/IGraphical.hpp"

namespace arc
{
    class AGraphical : public IGraphical
    {
    public:
        AGraphical();
        ~AGraphical();

        virtual std::list<arc::Event>   events() = 0;
        virtual void                    draw(const arc::IScreen& screen) = 0;
        

    };
} // namespace arc


#endif /* !AGRAPHICAL_HPP_ */
