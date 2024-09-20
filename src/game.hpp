#ifndef SNAKE_GAMEH
#define SNAKE_GAMEH

#include "windowevents.hpp"

#include <queue>

namespace Snake
{
    enum CellType
    {
        AIR,
        SNAKE_HEAD,
        DEAD_SNAKE_HEAD,
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

    enum ActionType
    {
        HEAD_NORTH,
        HEAD_SOUTH,
        HEAD_EAST,
        HEAD_WEST
    };

    struct Action
    {
        Snake::ActionType type;
        unsigned long timestamp;
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

        Snake::Direction headDirection;

        bool paused = true;
        std::queue<Snake::Action> actionQueue;

    public:
        Game(const unsigned int width, const unsigned int height, const unsigned int initialSize, Snake::EventManager* const eventManager);
        ~Game();

        unsigned int getWidth();
        unsigned int getHeight();

        Snake::GridCell getCell(const unsigned int x, const unsigned int y);

    protected:
        void setCell(const unsigned int x, const unsigned int y, const Snake::GridCell cell);

    public:
        bool isValid();
        int init();
        int destroy();

        bool isRunning();
        void start();
        void stop();

    protected:
        void run();

        void update();
        void handleKey(const Snake::KeyStruct key);

        void generateGrid();

        void spawnApple();
    };
};
#endif