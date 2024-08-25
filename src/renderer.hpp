#ifndef SNAKE_RENDERERH
#define SNAKE_RENDERERH

#include "window.hpp"
#include "game.hpp"

namespace Snake
{
    class Renderer
    {
    protected:
        Snake::Window* window;

        Snake::Game* game;

        bool initialized = false;
        bool destroyed = false;
        bool running = false;

        void* rendererStruct;

    public:
        Renderer(Snake::Window* const window, Snake::Game* game);
        ~Renderer();

        bool isValid();
        void init();
        void destroy();

        bool isRunning();
        void start();
        void stop();
    };
};
#endif