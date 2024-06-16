/*
** EPITECH PROJECT, 2024
** ArcadeBTTF
** File description:
** AGame
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "../../common/IGame.hpp"

namespace arc
{
    class AGame : public IGame
    {
        public:
            AGame() = default;
            ~AGame() = default;

            virtual void            update(float elapsed, const std::list<arc::Event>& events) = 0;
            virtual void            draw(arc::IScreen& screen) = 0;
            unsigned int score() const override{return _score;};
        protected:
            unsigned int _score;
    };
    
} // namespace arc


#endif /* !AGAME_HPP_ */
