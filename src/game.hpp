#ifndef SNAKE_GAMEH
#define SNAKE_GAMEH

#include "windowevents.hpp"

namespace Snake
{
    enum GridCell
    {
        AIR,
        SNAKE_HEAD,
        SNAKE_TAIL,
        APPLE
    };

    // typedef unsigned char GridCell;

    class Game
    {
    protected:
        unsigned int width;
        unsigned int height;

        unsigned int initialSize;

        Snake::EventManager* eventManager;

        bool initialized = false;
        bool destroyed = false;
        bool running = false;

        GridCell* grid;

    public:
        Game(unsigned int width, unsigned int height, unsigned int initialSize, Snake::EventManager* const eventManager);
        ~Game();

        unsigned int getWidth();
        unsigned int getHeight();

        bool isValid();
        int init();
        int destroy();

        bool isRunning();
        void start();
        void stop();

    protected:
        void generateGrid();

        void spawnApple();
    };
};
#endif