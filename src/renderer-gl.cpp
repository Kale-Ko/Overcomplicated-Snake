#include "renderer.hpp"

#include "window.hpp"
#include "game.hpp"

#include <cstdlib>
#include <cstring>
#include <cmath>

#include <thread>

namespace Snake
{
    Snake::Renderer::Renderer(Snake::Window* window, Snake::Game* game)
    {
        this->window = window;

        this->game = game;
    }

    Snake::Renderer::~Renderer()
    {
        if (this->initialized && !this->destroyed)
        {
            this->destroy();
        }
    }

    bool Snake::Renderer::isValid()
    {
        return this->initialized && !this->destroyed;
    }

    int Snake::Renderer::init()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Renderer is destroyed.\n");
            return -2;
        }
        if (this->initialized)
        {
            fprintf(stderr, "Renderer is already initialized.\n");
            return -2;
        }

        this->initialized = true;

        // TODO

        return 1;
    }

    int Snake::Renderer::destroy()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Renderer is already destroyed.\n");
            return -2;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Renderer is not initialized.\n");
            return -2;
        }

        if (this->running)
        {
            this->stop();
        }

        this->destroyed = true;
        this->initialized = false;

        // TODO

        return 1;
    }

    void run(Snake::Renderer* const context)
    {
        // TODO

        while (context->isRunning())
        {
            // TODO
        }
    }

    bool Snake::Renderer::isRunning()
    {
        return this->running;
    }

    void Snake::Renderer::start()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Renderer is destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Renderer is not initialized.\n");
            return;
        }

        if (this->running)
        {
            fprintf(stderr, "Renderer is already running.\n");
            return;
        }

        this->running = true;

        std::thread runThread(&run, this);
        runThread.detach();
    }

    void Snake::Renderer::stop()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Renderer is destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Renderer is not initialized.\n");
            return;
        }

        if (!this->running)
        {
            fprintf(stderr, "Renderer is not running.\n");
            return;
        }

        this->running = false;
    }
}