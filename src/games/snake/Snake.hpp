/*
** EPITECH PROJECT, 2024
** B-OOP-400-NAN-4-1-arcade-florian.gaudin
** File description:
** snake
*/

#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

    #include "AGame.hpp"

namespace arca {
    class Snake : public AGame<30, 30> {
        public:
            Snake();
            ~Snake();

            void handleInput(GameInput input) override;
            void update() override;

            std::vector<std::unique_ptr<arca::Sprite>>::iterator getPebble();
            const GameOutput nextFrame(const GameInput &input) override;
            const std::list<arca::SpriteId> getUsedSprites() const override;

            void gameOver();
            bool isPositionFree(unsigned x, unsigned y, SpriteId id);

            void moveSnake();
            void growSnake();
            void doesntGrowSnake();

        protected:
            unsigned _score;
            GameInput::Direction _direction;
            GameInput::Direction _tempDirection;
            unsigned _tik;
            bool _gameOver;

        private:
    };

    class SnakeSprite : public Sprite {
        public:
            SnakeSprite(unsigned x, unsigned y, unsigned num);
            ~SnakeSprite();
            unsigned getNum() const;
        protected:

        private:
            unsigned _num;
    };

    class PebbleSprite : public Sprite {
        public:
            PebbleSprite();
            ~PebbleSprite();

        protected:

        private:
    };

    class BackSprite : public Sprite {
        public:
            BackSprite();
            ~BackSprite();

        protected:

        private:
    };

    class CharSprites : public Sprite {
        public:
            CharSprites(double x, double y, SpriteId type);
            ~CharSprites();
        protected:

        private:
    };
}


#endif /* !SNAKE_HPP_ */
