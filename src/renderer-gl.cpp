#include "renderer.hpp"

#include "renderer.hpp"
#include "game.hpp"

#include <cstdlib>
#include <cmath>
#include <cstring>
#include <thread>

namespace Snake {
    Snake::Renderer::Renderer(Snake::Window* window, Snake::Game* game) {
        this->window = window;

        this->game = game;
    }

    Snake::Renderer::~Renderer() {

    }

    void Snake::Renderer::init() {
        if (this->destroyed) {
            fprintf(stderr, "Renderer is destroyed.\n");
            return;
        }
        if (this->initialized) {
            fprintf(stderr, "Renderer is already initialized.\n");
            return;
        }

        this->initialized = true;

        // TODO
    }

    void Snake::Renderer::destroy() {
        if (this->destroyed) {
            fprintf(stderr, "Renderer is already destroyed.\n");
            return;
        }
        if (!this->initialized) {
            fprintf(stderr, "Renderer is not initialized.\n");
            return;
        }

        if (this->running) {
            this->stop();
        }

        this->destroyed = true;
        this->initialized = false;

        // TODO
    }

    void run(Snake::Renderer* context) {
        // TODO

        while (context->isRunning())
        {
            // TODO
        }
    }


    bool Snake::Renderer::isRunning() {
        return this->running;
    }

    void Snake::Renderer::start() {
        if (this->destroyed) {
            fprintf(stderr, "Renderer is destroyed.\n");
            return;
        }
        if (!this->initialized) {
            fprintf(stderr, "Renderer is not initialized.\n");
            return;
        }

        if (this->running) {
            fprintf(stderr, "Renderer is already running.\n");
            return;
        }

        this->running = true;

        std::thread runThread(&run, this);
        runThread.detach();
    }

    void Snake::Renderer::stop() {
        if (this->destroyed) {
            fprintf(stderr, "Renderer is destroyed.\n");
            return;
        }
        if (!this->initialized) {
            fprintf(stderr, "Renderer is not initialized.\n");
            return;
        }

        if (!this->running) {
            fprintf(stderr, "Renderer is not running.\n");
            return;
        }

        this->running = false;
    }
}