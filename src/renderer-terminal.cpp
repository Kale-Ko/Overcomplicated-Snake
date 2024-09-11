#include "renderer.hpp"

#include "window.hpp"
#include "game.hpp"

#include <cstdlib>
#include <cstring>
#include <cmath>

#include <thread>

#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

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

    Snake::Window* Snake::Renderer::getWindow()
    {
        return this->window;
    }

    Snake::Game* Snake::Renderer::getGame()
    {
        return this->game;
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

        return 1;
    }

    void run(Snake::Renderer* const context)
    {
        winsize ts;
        ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);

        for (int i = 0; i < ts.ws_row - 1; i++)
        {
            printf("\n");
        }

        while (context->isRunning())
        {
            printf("\x1b[H");

            for (int i = 0; i <= context->getGame()->getHeight() + 1; i++)
            {
                for (int j = 0; j <= context->getGame()->getWidth() + 1; j++)
                {
                    if ((i == 0 || i == context->getGame()->getHeight() + 1) && (j == 0 || j == context->getGame()->getWidth() + 1))
                    {
                        printf("+");
                        continue;
                    } else if (i == 0 || i == context->getGame()->getHeight() + 1)
                    {
                        printf("-");
                        continue;
                    } else if (j == 0 || j == context->getGame()->getWidth() + 1)
                    {
                        printf("|");
                        continue;
                    }

                    int x = j - 1;
                    int y = i - 1;

                    switch (context->getGame()->getCell(x, y))
                    {
                        case SNAKE_HEAD:
                            printf("+");
                            break;
                        case SNAKE_TAIL:
                            printf("#");
                            break;
                        case APPLE:
                            printf("@");
                            break;
                        default:
                            printf(" ");
                            break;
                    }
                }

                printf("\n");
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
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