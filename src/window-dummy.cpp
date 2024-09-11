#include "window.hpp"

#include "windowevents.hpp"

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
    struct DummyWindowStruct
    {
    };

    Snake::Window::Window(const char* const title, const Snake::WindowIcon* const icon, const Snake::WindowSize size, const bool resizable, const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const bool mouseLockEnabled)
        : title(title), icon(icon), size(size), resizable(resizable), position(position), positionAlign(positionAlign), monitorType(Snake::WindowMonitorType::PRIMARY), mouseLockEnabled(mouseLockEnabled)
    {
    }

    Snake::Window::Window(const char* const title, const Snake::WindowIcon* const icon, const Snake::WindowSize size, const bool resizable, const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const Snake::WindowMonitorType monitorType, const bool mouseLockEnabled)
        : title(title), icon(icon), size(size), resizable(resizable), position(position), positionAlign(positionAlign), monitorType(monitorType), mouseLockEnabled(mouseLockEnabled)
    {
    }

    Snake::Window::~Window()
    {
        if (this->initialized && !this->destroyed)
        {
            this->destroy();
        }
    }

    const char* Snake::Window::getTitle()
    {
        return this->title;
    }

    void Snake::Window::setTitle(const char* const title)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->title = title;
    }

    const Snake::WindowIcon* Snake::Window::getIcon()
    {
        return this->icon;
    }

    void Snake::Window::setIcon(const Snake::WindowIcon* const icon)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->icon = icon;
    }

    const Snake::WindowSize Snake::Window::getSize()
    {
        return this->size;
    }

    const bool Snake::Window::isResizable()
    {
        return this->resizable;
    }

    void Snake::Window::setSize(const Snake::WindowSize size)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->resizable)
        {
            fprintf(stderr, "Window is not resizable.\n");
            return;
        }

        this->size = size;
    }

    void Snake::Window::__setSize(const Snake::WindowSize size)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->size = size;
    }

    const Snake::WindowPosition Snake::Window::getPosition()
    {
        return this->position;
    }

    const Snake::WindowPositionAlign Snake::Window::getPositionAlign()
    {
        return this->positionAlign;
    }

    const Snake::WindowMonitorType Snake::Window::getMonitorType()
    {
        return this->monitorType;
    }

    void Snake::Window::setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->position = position;
        this->positionAlign = positionAlign;
    }

    void Snake::Window::setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const Snake::WindowMonitorType monitorType)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->position = position;
        this->positionAlign = positionAlign;
        this->monitorType = monitorType;
    }

    void Snake::Window::__setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->position = position;
        this->positionAlign = positionAlign;
    }

    Snake::EventManager* const Snake::Window::getEventManager()
    {
        return &this->eventManager;
    }

    bool Snake::Window::isValid()
    {
        return this->initialized && !this->destroyed;
    }

    int Snake::Window::init()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return -2;
        }
        if (this->initialized)
        {
            fprintf(stderr, "Window is already initialized.\n");
            return -2;
        }

        this->windowStruct = new Snake::DummyWindowStruct();
        this->initialized = true;

        return 1;
    }

    int Snake::Window::destroy()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is already destroyed.\n");
            return -2;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Window is not initialized.\n");
            return -2;
        }

        if (this->running)
        {
            this->stop();
        }

        this->destroyed = true;
        this->initialized = false;

        delete(Snake::DummyWindowStruct*) this->windowStruct;

        return 1;
    }

    void Snake::Window::show()
    {
    }

    void Snake::Window::hide()
    {
    }

    void Snake::Window::focus()
    {
    }

    void run(Snake::Window* const context, Snake::DummyWindowStruct* const windowStruct)
    {
        // TODO Handle SIGINT

        {
            termios tty;
            tcgetattr(STDIN_FILENO, &tty);

            tty.c_lflag &= ~ICANON;
            tty.c_lflag &= ~ECHO;

            tcsetattr(STDIN_FILENO, TCSANOW, &tty);
        }

        char* buf = new char[2];
        buf[1] = 0;

        while (context->isRunning())
        { // Not efficient but it works
            std::cin.read(buf, 1);
            if (std::cin.good())
            {
                std::string string = buf;
                context->getEventManager()->emitKeyDownEvent(0, 0, &string);
                context->getEventManager()->emitKeyUpEvent(0, 0, &string);
            }
        }

        delete[] buf;
    }

    bool Snake::Window::isRunning()
    {
        return this->running;
    }

    void Snake::Window::start()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Window is not initialized.\n");
            return;
        }

        if (this->running)
        {
            fprintf(stderr, "Window is already running.\n");
            return;
        }

        this->running = true;

        std::thread runThread(&run, this, (Snake::DummyWindowStruct*) this->windowStruct);
        runThread.detach();
    }

    void Snake::Window::stop()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Window is not initialized.\n");
            return;
        }

        if (!this->running)
        {
            fprintf(stderr, "Window is not running.\n");
            return;
        }

        this->running = false;
    }

    bool Snake::Window::isMouseLockEnabled()
    {
        return this->mouseLockEnabled;
    }

    bool Snake::Window::isMouseLocked()
    {
        return this->mouseLocked;
    }

    void Snake::Window::lockMouse()
    {
        this->mouseLocked = true;
    }

    void Snake::Window::unlockMouse()
    {
        this->mouseLocked = false;
    }
}