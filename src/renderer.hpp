#ifndef SNAKE_RENDERERH
#define SNAKE_RENDERERH

#include "window.hpp"
#include "game.hpp"

namespace Snake
{
    class Renderer
    {
    protected:
        Snake::Window* const window;

        Snake::Game* game;

        bool initialized = false;
        bool destroyed = false;
        bool running = false;

        void* rendererStruct;

    public:
        Renderer(Snake::Window* const window, Snake::Game* const game);
        ~Renderer();

        Snake::Window* getWindow();

        Snake::Game* getGame();

        bool isValid();
        int init();
        int destroy();

        bool isRunning();
        void start();
        void stop();
    };
};
#endif