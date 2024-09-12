#ifndef SNAKE_GAMEH
#define SNAKE_GAMEH

#include "windowevents.hpp"

namespace Snake
{
    enum CellType
    {
        AIR,
        SNAKE_HEAD,
        SNAKE_TAIL,
        APPLE
    };

    enum Direction
    {
        NONE,
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    struct GridCell
    {
        Snake::CellType type;
        Snake::Direction direction;
    };

    class Game
    {
    protected:
        const unsigned int width;
        const unsigned int height;

        const unsigned int initialSize;

        Snake::EventManager* const eventManager;

        bool initialized = false;
        bool destroyed = false;
        bool running = false;

        Snake::GridCell* grid;

        struct
        {
            unsigned int x;
            unsigned int y;
        } headPosition;

    public:
        Game(const unsigned int width, const unsigned int height, const unsigned int initialSize, Snake::EventManager* const eventManager);
        ~Game();

        unsigned int getWidth();
        unsigned int getHeight();
        Snake::GridCell getCell(const unsigned int x, const unsigned int y);
        void setCell(const unsigned int x, const unsigned int y, const Snake::GridCell cell);

        bool isValid();
        int init();
        int destroy();

        bool isRunning();
        void start();
        void stop();

        void update();

    protected:
        void generateGrid();

        void spawnApple();
    };
};
#endif