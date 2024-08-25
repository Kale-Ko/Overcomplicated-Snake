#ifndef SNAKE_GAMEH
#define SNAKE_GAMEH

#include "windowevents.hpp"

#include <vector>

namespace Snake
{
    class Game
    {
    protected:
        unsigned int width;
        unsigned int height;

        Snake::EventManager* eventManager;

        bool initialized = false;
        bool destroyed = false;
        bool running = false;

        unsigned char* grid;

    public:
        Game(unsigned int width, unsigned int height, Snake::EventManager* const eventManager);
        ~Game();

        bool isValid();
        void init();
        void destroy();

        bool isRunning();
        void start();
        void stop();
    };
};
#endif