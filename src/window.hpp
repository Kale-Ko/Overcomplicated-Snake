#ifndef SNAKE_WINDOWH
#define SNAKE_WINDOWH

#include "windowevents.hpp"

namespace Snake
{
    struct WindowSize
    {
        unsigned int width;
        unsigned int height;
    };

    struct WindowPosition
    {
        signed int x;
        signed int y;
    };

    enum WindowPositionAlign
    {
        TOP_LEFT,
        CENTER
    };

    enum WindowMonitorType
    {
        PRIMARY,
        CURRENT
    };

    struct WindowIcon
    {
        unsigned int width;
        unsigned int height;

        unsigned char* data;
    };

    class Window
    {
    protected:
        const char* title;
        const Snake::WindowIcon* icon;

        Snake::WindowSize size;
        bool resizable;

        Snake::WindowPosition position;
        Snake::WindowPositionAlign positionAlign;
        Snake::WindowMonitorType monitorType;

        bool mouseLockEnabled;
        bool mouseLocked = false;

        bool initialized = false;
        bool destroyed = false;
        bool running = false;

        void* windowStruct;

        Snake::EventManager eventManager;

    public:
        Window(const char* const title, const Snake::WindowIcon* const icon, const Snake::WindowSize size, const bool resizable, const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const bool mouseLockEnabled);
        Window(const char* const title, const Snake::WindowIcon* const icon, const Snake::WindowSize size, const bool resizable, const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const Snake::WindowMonitorType monitorType, const bool mouseLockEnabled);
        ~Window();

        const char* getTitle();
        void setTitle(const char* const title);

        const Snake::WindowIcon* getIcon();
        void setIcon(const Snake::WindowIcon* const icon);

        const Snake::WindowSize getSize();
        const bool isResizable();
        void setSize(const Snake::WindowSize size);
        void __setSize(const Snake::WindowSize size);

        const Snake::WindowPosition getPosition();
        const Snake::WindowPositionAlign getPositionAlign();
        const Snake::WindowMonitorType getMonitorType();
        void setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign);
        void setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, Snake::WindowMonitorType monitorType);
        void __setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign);

        Snake::EventManager* const getEventManager();

        bool isValid();
        int init();
        int destroy();

        void show();
        void hide();
        void focus();

        bool isRunning();
        void start();
        void stop();

        bool isMouseLockEnabled();
        bool isMouseLocked();
        void lockMouse();
        void unlockMouse();
    };
};
#endif