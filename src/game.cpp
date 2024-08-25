#include "game.hpp"

#include <cstdlib>
#include <cstring>

#include <thread>

namespace Snake
{
    Snake::Game::Game(unsigned int width, unsigned int height, Snake::EventManager* const eventManager)
    {
        this->width = width;
        this->height = height;

        this->eventManager = eventManager;
    }

    Snake::Game::~Game()
    {
        if (this->initialized && !this->destroyed)
        {
            this->destroy();
        }
    }

    bool Snake::Game::isValid()
    {
        return this->initialized && !this->destroyed;
    }

    void Snake::Game::init()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Game is destroyed.\n");
            return;
        }
        if (this->initialized)
        {
            fprintf(stderr, "Game is already initialized.\n");
            return;
        }

        // TODO Init

        this->grid = new GridCell[this->width * this->height];
        this->initialized = true;
    }

    void Snake::Game::destroy()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Game is already destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Game is not initialized.\n");
            return;
        }

        if (this->running)
        {
            this->stop();
        }

        this->destroyed = true;
        this->initialized = false;

        // TODO Destroy
    }

    bool Snake::Game::isRunning()
    {
        return this->running;
    }

    void run(Snake::Game* const context)
    {
        // TODO
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
};