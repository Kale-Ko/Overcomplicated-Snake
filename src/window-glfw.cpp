#include "window.hpp"

#include "windowevents.hpp"

#include <cstdlib>
#include <cstring>
#include <cmath>

#include <thread>
#include <map>
#include <algorithm>

#include <GLFW/glfw3.h>

namespace Snake
{
    struct GLFWWindowStruct
    {
        GLFWwindow* window;

        WindowPosition screenOffset;
        WindowSize screenSize;
    };

    static int* glfwRefCount = new int{ 0 };

    static std::map<GLFWwindow* const, Snake::Window* const> glfwWindowMap;

    static Snake::Window* const glfwGetContextFromWindow(GLFWwindow* const window)
    {
        return glfwWindowMap.at(window);
    }

    Snake::Window::Window(const char* const title, const Snake::WindowIcon* const icon, const Snake::WindowSize size, const bool resizable, const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const bool mouseLockEnabled)
    {
        this->title = title;
        this->icon = icon;

        this->size = size;
        this->resizable = resizable;

        this->position = position;
        this->positionAlign = positionAlign;
        this->monitorType = WindowMonitorType::PRIMARY;

        this->mouseLockEnabled = mouseLockEnabled;
    }

    Snake::Window::Window(const char* const title, const Snake::WindowIcon* const icon, const Snake::WindowSize size, const bool resizable, const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const Snake::WindowMonitorType monitorType, const bool mouseLockEnabled)
    {
        this->title = title;
        this->icon = icon;

        this->size = size;
        this->resizable = resizable;

        this->position = position;
        this->positionAlign = positionAlign;
        this->monitorType = monitorType;

        this->mouseLockEnabled = mouseLockEnabled;
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

        if (this->initialized)
        {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

            glfwSetWindowTitle(windowStruct->window, (char*) this->title);
        }
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

        if (this->initialized)
        {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

            if (icon != NULL)
            {
                GLFWimage glfwIcon;
                glfwIcon.width = this->icon->width;
                glfwIcon.height = this->icon->height;
                glfwIcon.pixels = this->icon->data;
                glfwSetWindowIcon(windowStruct->window, 1, &glfwIcon);
            } else
            {
                glfwSetWindowIcon(windowStruct->window, 0, NULL);
            }
        }
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

        if (this->initialized)
        {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

            if (this->position.x < 0 || this->position.x + size.width >= windowStruct->screenSize.width || this->position.y < 0 || this->position.y + size.height >= windowStruct->screenSize.height)
            {
                fprintf(stderr, "Size is outside screen bounds.\n");
                return;
            }

            glfwSetWindowSize(windowStruct->window, this->size.width, this->size.height);
        }
    }

    void Snake::Window::__setSize(const Snake::WindowSize size)
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

        if (this->initialized)
        {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

            if (position.x < 0 || position.x + this->size.width >= windowStruct->screenSize.width || position.y < 0 || position.y + this->size.height >= windowStruct->screenSize.height)
            {
                fprintf(stderr, "Position is outside screen bounds.\n");
                return;
            }

            {
                GLFWmonitor* monitor = NULL;
                switch (this->monitorType)
                {
                    case PRIMARY:
                        monitor = glfwGetPrimaryMonitor();
                        if (monitor == NULL)
                        {
                            fprintf(stderr, "Failed to find primary monitor.\n");
                            return;
                        }
                        break;
                    case CURRENT:
                        fprintf(stderr, "GLFW does not support CURRENT monitor mode.\n");
                        return;
                }

                glfwGetMonitorWorkarea(monitor, &windowStruct->screenOffset.x, &windowStruct->screenOffset.y, (int*) &windowStruct->screenSize.width, (int*) &windowStruct->screenSize.height);
            }

            switch (this->positionAlign)
            {
                case TOP_LEFT:
                    glfwSetWindowPos(windowStruct->window, this->position.x, this->position.y);
                    break;
                case CENTER:
                    glfwSetWindowPos(windowStruct->window, this->position.x + windowStruct->screenOffset.x + ((windowStruct->screenSize.width / 2) - (this->size.width / 2)), this->position.y + windowStruct->screenOffset.y + ((windowStruct->screenSize.height / 2) - (this->size.height / 2)));
                    break;
            }
        }
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

        if (this->initialized)
        {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

            if (position.x < 0 || position.x + this->size.width >= windowStruct->screenSize.width || position.y < 0 || position.y + this->size.height >= windowStruct->screenSize.height)
            {
                fprintf(stderr, "Position is outside screen bounds.\n");
                return;
            }

            {
                GLFWmonitor* monitor = NULL;
                switch (this->monitorType)
                {
                    case PRIMARY:
                        monitor = glfwGetPrimaryMonitor();
                        if (monitor == NULL)
                        {
                            fprintf(stderr, "Failed to find primary monitor.\n");
                            return;
                        }
                        break;
                    case CURRENT:
                        fprintf(stderr, "GLFW does not support CURRENT monitor mode.\n");
                        return;
                }

                glfwGetMonitorWorkarea(monitor, &windowStruct->screenOffset.x, &windowStruct->screenOffset.y, (int*) &windowStruct->screenSize.width, (int*) &windowStruct->screenSize.height);
            }

            switch (this->positionAlign)
            {
                case TOP_LEFT:
                    glfwSetWindowPos(windowStruct->window, this->position.x, this->position.y);
                    break;
                case CENTER:
                    glfwSetWindowPos(windowStruct->window, this->position.x + windowStruct->screenOffset.x + ((windowStruct->screenSize.width / 2) - (this->size.width / 2)), this->position.y + windowStruct->screenOffset.y + ((windowStruct->screenSize.height / 2) - (this->size.height / 2)));
                    break;
            }
        }
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

        if (*glfwRefCount == 0)
        {
            (*glfwRefCount)++;

            if (glfwInit() != GLFW_TRUE)
            {
                fprintf(stderr, "Failed to initialize GLFW.\n");
                return -1;
            }
        }

        this->windowStruct = new Snake::GLFWWindowStruct();
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;
        this->initialized = true;

        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_RESIZABLE, this->resizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

        windowStruct->window = glfwCreateWindow(this->size.width, this->size.height, (char*) this->title, NULL, NULL);
        if (windowStruct->window == NULL)
        {
            fprintf(stderr, "Failed to create GLFW window.\n");
            return -1;
        }

        glfwWindowMap.insert(std::make_pair(windowStruct->window, this));

        if (icon != NULL)
        {
            GLFWimage glfwIcon;
            glfwIcon.width = this->icon->width;
            glfwIcon.height = this->icon->height;
            glfwIcon.pixels = this->icon->data;
            glfwSetWindowIcon(windowStruct->window, 1, &glfwIcon);
        } else
        {
            glfwSetWindowIcon(windowStruct->window, 0, NULL);
        }

        glfwSetWindowSize(windowStruct->window, this->size.width, this->size.height);

        if (!this->resizable)
        {
            glfwSetWindowSizeLimits(windowStruct->window, this->size.width, this->size.height, this->size.width, this->size.height);
        }

        {
            windowStruct->screenOffset = WindowPosition{ 0, 0 };
            windowStruct->screenSize = WindowSize{ 0, 0 };

            GLFWmonitor* monitor = NULL;
            switch (this->monitorType)
            {
                case PRIMARY:
                    monitor = glfwGetPrimaryMonitor();
                    if (monitor == NULL)
                    {
                        fprintf(stderr, "Failed to find primary monitor.\n");
                        return -1;
                    }
                    break;
                case CURRENT:
                    fprintf(stderr, "GLFW does not support CURRENT monitor mode.\n");
                    return -1;
            }

            glfwGetMonitorWorkarea(monitor, &windowStruct->screenOffset.x, &windowStruct->screenOffset.y, (int*) &windowStruct->screenSize.width, (int*) &windowStruct->screenSize.height);
        }

        switch (this->positionAlign)
        {
            case TOP_LEFT:
                glfwSetWindowPos(windowStruct->window, this->position.x, this->position.y);
                break;
            case CENTER:
                glfwSetWindowPos(windowStruct->window, this->position.x + windowStruct->screenOffset.x + ((windowStruct->screenSize.width / 2) - (this->size.width / 2)), this->position.y + windowStruct->screenOffset.y + ((windowStruct->screenSize.height / 2) - (this->size.height / 2)));
                break;
        }

        // glfwMakeContextCurrent(windowStruct->window);

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

        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

        glfwWindowMap.erase(windowStruct->window);

        glfwDestroyWindow(windowStruct->window);

        (*glfwRefCount)--;
        if (*glfwRefCount == 0)
        {
            glfwTerminate();
        }

        delete(Snake::GLFWWindowStruct*) this->windowStruct;

        return 1;
    }

    void Snake::Window::show()
    {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

        glfwShowWindow(windowStruct->window);
    }

    void Snake::Window::hide()
    {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

        glfwHideWindow(windowStruct->window);
    }

    void Snake::Window::focus()
    {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

        glfwFocusWindow(windowStruct->window);
    }

    void glfwWindowFocusCallback(GLFWwindow* const window, int focused)
    {
        Snake::Window* context = glfwGetContextFromWindow(window);

        if (focused == GLFW_TRUE)
        {
            if (context->isMouseLockEnabled() && !context->isMouseLocked())
            {
                context->lockMouse();
            }

            context->getEventManager()->emitWindowFocusEvent();
        } else if (focused == GLFW_FALSE)
        {
            if (context->isMouseLocked())
            {
                context->unlockMouse();
            }

            context->getEventManager()->emitWindowUnfocusEvent();
        }
    }

    void glfwWindowCloseCallback(GLFWwindow* const window)
    {
        Snake::Window* context = glfwGetContextFromWindow(window);

        context->getEventManager()->emitWindowCloseEvent();

        context->stop();
    }

    void glfwWindowPositionCallback(GLFWwindow* const window, int x, int y)
    {
        Snake::Window* context = glfwGetContextFromWindow(window);

        Snake::WindowPosition previousPosition;
        previousPosition = context->getPosition();

        context->__setPosition(Snake::WindowPosition{ .x = x, .y = y }, Snake::WindowPositionAlign::TOP_LEFT); // TODO Don't change position align

        if (x != previousPosition.x || y != previousPosition.y)
        {
            context->getEventManager()->emitWindowMoveEvent(x, y);
        }
    }

    void glfwWindowSizeCallback(GLFWwindow* const window, int width, int height)
    {
        Snake::Window* context = glfwGetContextFromWindow(window);

        Snake::WindowSize previousSize;
        previousSize = context->getSize();

        context->__setSize(Snake::WindowSize{ .width = (unsigned int) width, .height = (unsigned int) height });

        if ((unsigned int) width != previousSize.width || (unsigned int) height != previousSize.height)
        {
            context->getEventManager()->emitWindowResizeEvent(width, height);
        }
    }

    void glfwMouseMoveCallback(GLFWwindow* const window, double xd, double yd)
    {
        Snake::Window* context = glfwGetContextFromWindow(window);

        int x = (int) floor(xd);
        int y = (int) floor(yd);

        if (context->isMouseLockEnabled() && context->isMouseLocked())
        {
            if (x == (int) context->getSize().width / 2 && y == (int) context->getSize().height / 2)
            {
                return;
            }

            context->getEventManager()->emitMouseMoveEvent(x - (context->getSize().width / 2), y - (context->getSize().height / 2));

            glfwSetCursorPos(window, context->getSize().width / 2, context->getSize().height / 2);
        } else
        {
            context->getEventManager()->emitMouseMoveEvent(x, y);
        }
    }

    void glfwMouseScrollCallback(GLFWwindow* const window, double xd, double yd)
    {
        Snake::Window* context = glfwGetContextFromWindow(window);

        int x = (int) floor(xd);
        int y = (int) floor(yd);

        context->getEventManager()->emitMouseScrollEvent(x, y);
    }

    void glfwButtonCallback(GLFWwindow* const window, int button, int action, int modifiers)
    {
        Snake::Window* context = glfwGetContextFromWindow(window);

        if (action == GLFW_PRESS || action == GLFW_REPEAT)
        {
            if (context->isMouseLockEnabled() && !context->isMouseLocked())
            {
                context->lockMouse();
            }

            context->getEventManager()->emitButtonDownEvent(button, modifiers, NULL);
        } else if (action == GLFW_RELEASE)
        {
            context->getEventManager()->emitButtonUpEvent(button, modifiers, NULL);
        }
    }

    void glfwKeyCallback(GLFWwindow* const window, int keyCode, int scanCode, int action, int modifiers)
    {
        Snake::Window* context = glfwGetContextFromWindow(window);

        if (action == GLFW_PRESS)
        {
            if (context->isMouseLocked() && keyCode == GLFW_KEY_ESCAPE)
            {
                context->unlockMouse();
            }

            context->getEventManager()->emitKeyDownEvent(keyCode, modifiers, NULL);
        } else if (action == GLFW_RELEASE)
        {
            context->getEventManager()->emitKeyUpEvent(keyCode, modifiers, NULL);
        } else if (action == GLFW_REPEAT)
        {
            context->getEventManager()->emitKeyUpEvent(keyCode, modifiers, NULL);

            context->getEventManager()->emitKeyDownEvent(keyCode, modifiers, NULL);
        }
    }

    void run(Snake::Window* context, Snake::GLFWWindowStruct* windowStruct)
    {
        // glfwMakeContextCurrent(windowStruct->window);

        glfwSetWindowFocusCallback(windowStruct->window, &glfwWindowFocusCallback);
        glfwSetWindowCloseCallback(windowStruct->window, &glfwWindowCloseCallback);
        glfwSetWindowPosCallback(windowStruct->window, &glfwWindowPositionCallback);
        glfwSetWindowSizeCallback(windowStruct->window, &glfwWindowSizeCallback);
        glfwSetCursorPosCallback(windowStruct->window, &glfwMouseMoveCallback);
        glfwSetScrollCallback(windowStruct->window, &glfwMouseScrollCallback);
        glfwSetMouseButtonCallback(windowStruct->window, &glfwButtonCallback);
        glfwSetKeyCallback(windowStruct->window, &glfwKeyCallback);

        while (context->isRunning())
        {
            glfwPollEvents();
        }
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

        std::thread runThread(&run, this, (Snake::GLFWWindowStruct*) this->windowStruct);
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
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

        glfwSetInputMode(windowStruct->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        this->mouseLocked = true;
    }

    void Snake::Window::unlockMouse()
    {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*) this->windowStruct;

        glfwSetInputMode(windowStruct->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        this->mouseLocked = false;
    }
};