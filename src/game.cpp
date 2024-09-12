#include "game.hpp"

#include <cstdlib>
#include <cstring>

#include <thread>

namespace Snake
{
    Snake::Game::Game(const unsigned int width, const unsigned int height, const unsigned int initialSize, Snake::EventManager* const eventManager)
        : width(width), height(height), initialSize(initialSize), eventManager(eventManager)
    {
    }

    Snake::Game::~Game()
    {
        if (this->initialized && !this->destroyed)
        {
            this->destroy();
        }
    }

    unsigned int Snake::Game::getWidth()
    {
        return this->width;
    }

    unsigned int Snake::Game::getHeight()
    {
        return this->height;
    }

    Snake::GridCell Snake::Game::getCell(const unsigned int x, const unsigned int y)
    {
        return this->grid[(y * this->width) + x];
    }

    void Snake::Game::setCell(const unsigned int x, const unsigned int y, Snake::GridCell cell)
    {
        this->grid[(y * this->width) + x] = cell;
    }

    bool Snake::Game::isValid()
    {
        return this->initialized && !this->destroyed;
    }

    int Snake::Game::init()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Game is destroyed.\n");
            return -2;
        }
        if (this->initialized)
        {
            fprintf(stderr, "Game is already initialized.\n");
            return -2;
        }

        this->grid = new GridCell[this->width * this->height];
        this->initialized = true;

        this->generateGrid();

        return 1;
    }

    int Snake::Game::destroy()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Game is already destroyed.\n");
            return -2;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Game is not initialized.\n");
            return -2;
        }

        if (this->running)
        {
            this->stop();
        }

        this->destroyed = true;
        this->initialized = false;

        delete this->grid;

        return 1;
    }

    bool Snake::Game::isRunning()
    {
        return this->running;
    }

    void run(Snake::Game* const context)
    {
        while (context->isRunning())
        {
            context->update();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void Snake::Game::start()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Game is destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Game is not initialized.\n");
            return;
        }

        if (this->running)
        {
            fprintf(stderr, "Game is already running.\n");
            return;
        }

        this->running = true;

        std::thread runThread(&run, this);
        runThread.detach();
    }

    void Snake::Game::stop()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Game is destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Game is not initialized.\n");
            return;
        }

        if (!this->running)
        {
            fprintf(stderr, "Game is not running.\n");
            return;
        }

        this->running = false;
    }

    void Snake::Game::update()
    {
    }

    void Snake::Game::generateGrid()
    {
        for (int y = 0; y < this->height; y++)
        {
            for (int x = 0; x < this->width; x++)
            {
                this->setCell(x, y, Snake::GridCell{ .type = Snake::CellType::AIR, .direction = Snake::Direction::NONE });
            }
        }

        this->headPosition = { .x = this->width / 2, .y = this->height / 2 };

        this->setCell(this->headPosition.x, this->headPosition.y, Snake::GridCell{ .type = Snake::CellType::SNAKE_HEAD, .direction = Snake::Direction::EAST });

        for (int x = (this->headPosition.x) - 1; x > (this->headPosition.x) - this->initialSize; x--)
        {
            this->setCell(x, this->headPosition.y, Snake::GridCell{ .type = Snake::CellType::SNAKE_TAIL, .direction = Snake::Direction::EAST });
        }

        this->spawnApple();
    }

    void Snake::Game::spawnApple()
    {
        int x = floor(randomDouble() * this->width);
        int y = floor(randomDouble() * this->height);

        if (this->getCell(x, y).type == CellType::AIR)
        {
            this->setCell(x, y, Snake::GridCell{ .type = Snake::CellType::APPLE, .direction = Snake::Direction::NONE });
        } else
        {
            this->spawnApple();
        }
    }
};