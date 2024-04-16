#ifndef SNAKE_WINDOWH
#define SNAKE_WINDOWH

#include "windowevents.hpp"

namespace Snake {
    struct WindowSize {
        unsigned int width;
        unsigned int height;
    };

    struct WindowPosition {
        int x;
        int y;
    };

    enum WindowPositionAlign {
        TOP_LEFT,
        CENTER
    };

    struct WindowIcon {
        unsigned int width;
        unsigned int height;

        unsigned char* data;
    };

    class Window {
    protected:
        unsigned char* title;
        Snake::WindowIcon* icon;

        Snake::WindowSize size;
        bool resizable;

        Snake::WindowPosition position;
        Snake::WindowPositionAlign positionAlign;

        bool mouseLockEnabled;
        bool mouseLocked = false;

        bool initialized = false;
        bool destroyed = false;
        bool running = false;

        long windowId;
        void* windowStruct;

        Snake::EventManager eventManager = Snake::EventManager();

    public:
        Window(unsigned char* title, Snake::WindowIcon* icon, Snake::WindowSize size, bool resizable, Snake::WindowPosition position, Snake::WindowPositionAlign positionAlign, bool mouseLockEnabled);
        ~Window();

        unsigned char* getTitle();
        void setTitle(unsigned char* title);

        Snake::WindowIcon* getIcon();
        void setIcon(Snake::WindowIcon* icon);

        Snake::WindowSize getSize();
        bool isResizable();
        void setSize(Snake::WindowSize size);
        void setRawSize(Snake::WindowSize size);

        Snake::WindowPosition getPosition();
        Snake::WindowPositionAlign getPositionAlign();
        void setPosition(Snake::WindowPosition position, Snake::WindowPositionAlign align);
        void setRawPosition(Snake::WindowPosition position, Snake::WindowPositionAlign align);

        Snake::EventManager* getEventManager();

        bool isValid();
        void init();
        void destroy();

        void show();
        void hide();
        void focus();

        bool isRunning();
        void start();
        void stop();

        bool isMouseLockEnabled();
        bool isMouseLocked();
        inline void lockMouse();
        inline void unlockMouse();
    };
};
#endif