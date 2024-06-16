/*
** EPITECH PROJECT, 2024
** B-OOP-400-NAN-4-1-arcade-florian.gaudin
** File description:
** snake
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include "../include/AGame.hpp"

namespace arc {
    class Snake : public AGame {
        public:
            enum SpriteId {
                SNAKE_HEAD,
                SNAKE_BODY,
                SNAKE_PEBBLE,
                SNAKE_TAIL,
                WALLS,
                FLOOR_ROOF
            };
            class Sprite {
                public:
                    Sprite(unsigned x, unsigned y, SpriteId id);
                    ~Sprite();

                    unsigned x;
                    unsigned y;
                    SpriteId id;
            };
        public:
            Snake();
            ~Snake();

            virtual void update(float elapsed, const std::list<arc::Event>& events);
            virtual void draw(arc::IScreen& screen);

            std::vector<Sprite>::iterator getPebble();

            bool isPositionFree(unsigned x, unsigned y, SpriteId id);
            std::pair<unsigned, unsigned> getSpritePosition(std::vector<Sprite>::iterator sprite);
        

            void moveSnake();
            void growSnake();
            void doesntGrowSnake();

            void randomPebble();

        protected:
            Event _direction;
            Event _tempDirection;
            float _tik;
            bool _gameOver;
            std::vector<Sprite> _sprites;
            bool _noMove;

        private:
    };
}


#endif /* !SNAKE_HPP_ */
