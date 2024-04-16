#include "window.hpp"

#include "windowevents.hpp"

#include <cstdlib>
#include <cmath>
#include <cstring>
#include <thread>

#include <map>
#include <algorithm>

#include <GLFW/glfw3.h>

namespace Snake {
    struct GLFWWindowStruct {
        GLFWwindow* window;
    };

    static std::map<GLFWwindow*, Snake::Window*> windowMap;

    static Snake::Window* glfwGetContextFromWindow(GLFWwindow* window) {
        return windowMap.at(window);
    }

    Snake::Window::Window(unsigned char* title, Snake::WindowIcon* icon, Snake::WindowSize size, bool resizable, WindowPosition position, Snake::WindowPositionAlign positionAlign, bool mouseLockEnabled) {
        this->title = title;
        this->icon = icon;

        this->size = size;
        this->resizable = resizable;

        this->position = position;
        this->positionAlign = positionAlign;

        this->mouseLockEnabled = mouseLockEnabled;
    }

    Snake::Window::~Window() {
        if (this->initialized && !this->destroyed) {
            this->destroy();
        }
    }

    unsigned char* Snake::Window::getTitle() {
        return this->title;
    }

    void Snake::Window::setTitle(unsigned char* title) {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->title = title;

        if (this->initialized) {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

            glfwSetWindowTitle(windowStruct->window, (char*)this->title);
        }
    }

    Snake::WindowIcon* Snake::Window::getIcon() {
        return this->icon;
    }

    void Snake::Window::setIcon(Snake::WindowIcon* icon) {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->icon = icon;

        if (this->initialized) {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

            if (icon != NULL) {
                GLFWimage glfwIcon;
                glfwIcon.width = this->icon->width;
                glfwIcon.height = this->icon->height;
                glfwIcon.pixels = this->icon->data;
                glfwSetWindowIcon(windowStruct->window, 1, &glfwIcon);
            }
            else {
                glfwSetWindowIcon(windowStruct->window, 0, NULL);
            }
        }
    }

    Snake::WindowSize Snake::Window::getSize() {
        return this->size;
    }

    bool Snake::Window::isResizable() {
        return this->resizable;
    }

    void Snake::Window::setSize(Snake::WindowSize size) {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->resizable) {
            fprintf(stderr, "Window is not resizable.\n");
            return;
        }

        this->size = size;

        if (this->initialized) {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

            glfwSetWindowSize(windowStruct->window, this->size.width, this->size.height);
        }
    }

    void Snake::Window::setRawSize(Snake::WindowSize size) {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->resizable) {
            fprintf(stderr, "Window is not resizable.\n");
            return;
        }

        this->size = size;
    }

    Snake::WindowPosition Snake::Window::getPosition() {
        return this->position;
    }

    Snake::WindowPositionAlign Snake::Window::getPositionAlign() {
        return this->positionAlign;
    }

    void Snake::Window::setPosition(WindowPosition position, Snake::WindowPositionAlign align) {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->position = position;
        this->positionAlign = positionAlign;

        if (this->initialized) {
            Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

            switch (this->positionAlign) {
            case TOP_LEFT:
                glfwSetWindowPos(windowStruct->window, this->position.x, this->position.y);
                break;
            case CENTER:
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                int x, y, width, height;
                glfwGetMonitorWorkarea(monitor, &x, &y, &width, &height);

                glfwSetWindowPos(windowStruct->window, this->position.x + x + ((width / 2) - (this->size.width / 2)), this->position.y + y + ((height / 2) - (this->size.height / 2)));
                break;
            }
        }
    }

    void Snake::Window::setRawPosition(WindowPosition position, Snake::WindowPositionAlign align) {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->position = position;
        this->positionAlign = positionAlign;
    }

    Snake::EventManager* Snake::Window::getEventManager() {
        return &this->eventManager;
    }

    bool Snake::Window::isValid() {
        return this->initialized && !this->destroyed;
    }

    void Snake::Window::init() {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (this->initialized) {
            fprintf(stderr, "Window is already initialized.\n");
            return;
        }

        if (glfwInit() != GLFW_TRUE) {
            fprintf(stderr, "Failed to initialize GLFW.\n");
            return;
        }

        this->windowStruct = new Snake::GLFWWindowStruct();
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;
        this->initialized = true;

        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_RESIZABLE, this->resizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

        windowStruct->window = glfwCreateWindow(this->size.width, this->size.height, (char*)this->title, NULL, NULL);
        if (windowStruct->window == 0) {
            fprintf(stderr, "Failed to create GLFW window.\n");
            return;
        }

        windowMap.insert(std::make_pair(windowStruct->window, this));

        if (icon != NULL) {
            GLFWimage glfwIcon;
            glfwIcon.width = this->icon->width;
            glfwIcon.height = this->icon->height;
            glfwIcon.pixels = this->icon->data;
            glfwSetWindowIcon(windowStruct->window, 1, &glfwIcon);
        }
        else {
            glfwSetWindowIcon(windowStruct->window, 0, NULL);
        }

        glfwSetWindowSize(windowStruct->window, this->size.width, this->size.height);

        if (!this->resizable) {
            glfwSetWindowSizeLimits(windowStruct->window, this->size.width, this->size.height, this->size.width, this->size.height);
        }

        switch (this->positionAlign) {
        case TOP_LEFT:
            glfwSetWindowPos(windowStruct->window, this->position.x, this->position.y);
            break;
        case CENTER:
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            int x, y, width, height;
            glfwGetMonitorWorkarea(monitor, &x, &y, &width, &height);

            glfwSetWindowPos(windowStruct->window, this->position.x + x + ((width / 2) - (this->size.width / 2)), this->position.y + y + ((height / 2) - (this->size.height / 2)));
            break;
        }

        // glfwMakeContextCurrent(windowStruct->window);
    }

    void Snake::Window::destroy() {
        if (this->destroyed) {
            fprintf(stderr, "Window is already destroyed.\n");
            return;
        }
        if (!this->initialized) {
            fprintf(stderr, "Window is not initialized.\n");
            return;
        }

        if (this->running) {
            this->stop();
        }

        this->destroyed = true;
        this->initialized = false;

        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

        windowMap.erase(windowStruct->window);

        glfwDestroyWindow(windowStruct->window);

        glfwTerminate();

        delete (Snake::GLFWWindowStruct*)this->windowStruct;
    }

    void Snake::Window::show() {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

        glfwShowWindow(windowStruct->window);
    }

    void Snake::Window::hide() {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

        glfwHideWindow(windowStruct->window);
    }

    void Snake::Window::focus() {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

        glfwFocusWindow(windowStruct->window);
    }

    void glfwWindowFocusCallback(GLFWwindow* window, int focused) {
        Snake::Window* context = glfwGetContextFromWindow(window);

        if (focused == GLFW_TRUE) {
            if (context->isMouseLockEnabled() && !context->isMouseLocked())
            {
                context->lockMouse();
            }

            context->getEventManager()->emitWindowFocusEvent();
        }
        else {
            if (context->isMouseLocked())
            {
                context->unlockMouse();
            }

            context->getEventManager()->emitWindowUnfocusEvent();
        }
    }

    void glfwKeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int modifiers) {
        Snake::Window* context = glfwGetContextFromWindow(window);

        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            if (context->isMouseLocked() && keyCode == GLFW_KEY_ESCAPE)
            {
                context->unlockMouse();
            }

            context->getEventManager()->emitKeyDownEvent(keyCode, modifiers, NULL);
        }
        else {
            context->getEventManager()->emitKeyUpEvent(keyCode, modifiers, NULL);
        }
    }

    void glfwButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {
        Snake::Window* context = glfwGetContextFromWindow(window);

        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            if (context->isMouseLockEnabled() && !context->isMouseLocked())
            {
                context->lockMouse();
            }

            context->getEventManager()->emitButtonDownEvent(button, modifiers, NULL);
        }
        else {
            context->getEventManager()->emitButtonUpEvent(button, modifiers, NULL);
        }
    }

    void glfwMouseMoveCallback(GLFWwindow* window, double xd, double yd) {
        Snake::Window* context = glfwGetContextFromWindow(window);

        int x = (int)round(xd);
        int y = (int)round(yd);

        if (context->isMouseLockEnabled() && context->isMouseLocked())
        {
            if (x == context->getSize().width / 2 && y == context->getSize().height / 2)
            {
                return;
            }

            context->getEventManager()->emitMouseMoveEvent(x - (context->getSize().width / 2), y - (context->getSize().height / 2));

            glfwSetCursorPos(window, context->getSize().width / 2, context->getSize().height / 2);
        }
        else
        {
            context->getEventManager()->emitMouseMoveEvent(x, y);
        }
    }

    void glfwMouseScrollCallback(GLFWwindow* window, double xd, double yd) {
        Snake::Window* context = glfwGetContextFromWindow(window);

        int x = (int)round(xd);
        int y = (int)round(yd);

        context->getEventManager()->emitMouseScrollEvent(x, y);
    }

    void glfwWindowPositionCallback(GLFWwindow* window, int x, int y) {
        Snake::Window* context = glfwGetContextFromWindow(window);

        context->setRawPosition(Snake::WindowPosition{ .x = x, .y = y }, Snake::WindowPositionAlign::TOP_LEFT); // TODO Don't change position align
    }

    void glfwWindowSizeCallback(GLFWwindow* window, int width, int height) {
        Snake::Window* context = glfwGetContextFromWindow(window);

        Snake::WindowSize previousSize;
        previousSize = context->getSize();

        context->setRawSize(Snake::WindowSize{ .width = (unsigned int)width, .height = (unsigned int)height });

        if (width != previousSize.width || height != previousSize.height)
        {
            context->getEventManager()->emitWindowResizeEvent(width, height);
        }
    }

    void glfwWindowCloseCallback(GLFWwindow* window) {
        Snake::Window* context = glfwGetContextFromWindow(window);

        context->stop();
    }

    void run(Snake::Window* context, Snake::GLFWWindowStruct* windowStruct) {
        // glfwMakeContextCurrent(windowStruct->window);

        if (context->isMouseLockEnabled()) {
            context->lockMouse();
        }

        glfwSetWindowFocusCallback(windowStruct->window, &glfwWindowFocusCallback);
        glfwSetKeyCallback(windowStruct->window, &glfwKeyCallback);
        glfwSetMouseButtonCallback(windowStruct->window, &glfwButtonCallback);
        glfwSetCursorPosCallback(windowStruct->window, &glfwMouseMoveCallback);
        glfwSetScrollCallback(windowStruct->window, &glfwMouseScrollCallback);
        glfwSetWindowPosCallback(windowStruct->window, &glfwWindowPositionCallback);
        glfwSetWindowSizeCallback(windowStruct->window, &glfwWindowSizeCallback);
        glfwSetWindowCloseCallback(windowStruct->window, &glfwWindowCloseCallback);

        while (context->isRunning()) {
            glfwPollEvents();
        }
    }

    bool Snake::Window::isRunning() {
        return this->running;
    }

    void Snake::Window::start() {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->initialized) {
            fprintf(stderr, "Window is not initialized.\n");
            return;
        }

        if (this->running) {
            fprintf(stderr, "Window is already running.\n");
            return;
        }

        this->running = true;

        std::thread runThread(&run, this, (Snake::GLFWWindowStruct*)this->windowStruct);
        runThread.detach();
    }

    void Snake::Window::stop() {
        if (this->destroyed) {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->initialized) {
            fprintf(stderr, "Window is not initialized.\n");
            return;
        }

        if (!this->running) {
            fprintf(stderr, "Window is not running.\n");
            return;
        }

        this->running = false;
    }

    bool Snake::Window::isMouseLockEnabled() {
        return this->mouseLockEnabled;
    }

    bool Snake::Window::isMouseLocked() {
        return this->mouseLocked;
    }

    inline void Snake::Window::lockMouse()
    {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

        glfwSetInputMode(windowStruct->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        this->mouseLocked = true;
    }

    inline void Snake::Window::unlockMouse()
    {
        Snake::GLFWWindowStruct* windowStruct = (Snake::GLFWWindowStruct*)this->windowStruct;

        this->mouseLocked = false;

        glfwSetInputMode(windowStruct->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
};