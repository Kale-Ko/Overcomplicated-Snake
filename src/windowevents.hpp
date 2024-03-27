#ifndef SNAKE_WINDOWEVENTSH
#define SNAKE_WINDOWEVENTSH

#include "keyboard.hpp"

#include <vector>

namespace Snake {
    class EventManager
    {
    protected:
        std::vector<void (*)()> windowFocusListeners;
        std::vector<void (*)()> windowUnfocusListeners;

        std::vector<void (*)(int x, int y)> windowMoveListeners;
        std::vector<void (*)(int width, int height)> windowResizeListeners;

        std::vector<void (*)(int x, int y)> mouseMoveListeners;
        std::vector<void (*)(int x, int y)> mouseScrollListeners;

        std::vector<void (*)(Snake::KeyStruct key)> keyDownListeners;
        std::vector<void (*)(Snake::KeyStruct key)> keyUpListeners;

        std::vector<void (*)(Snake::ButtonStruct button)> buttonDownListeners;
        std::vector<void (*)(Snake::ButtonStruct button)> buttonUpListeners;

    public:
        EventManager();
        ~EventManager();

        void emitWindowFocusEvent();
        void registerWindowFocusListener(void (*listener)());
        void unregisterWindowFocusListener(void (*listener)());

        void emitWindowUnfocusEvent();
        void registerWindowUnfocusListener(void (*listener)());
        void unregisterWindowUnfocusListener(void (*listener)());

        void emitWindowMoveEvent(int x, int y);
        void registerWindowMoveListener(void (*listener)(int x, int y));
        void unregisterWindowMoveListener(void (*listener)(int x, int y));

        void emitWindowResizeEvent(int width, int height);
        void registerWindowResizeListener(void (*listener)(int width, int height));
        void unregisterWindowResizeListener(void (*listener)(int width, int height));

        void emitMouseMoveEvent(int x, int y);
        void registerMouseMoveListener(void (*listener)(int x, int y));
        void unregisterMouseMoveListener(void (*listener)(int x, int y));

        void emitMouseScrollEvent(int x, int y);
        void registerMouseScrollListener(void (*listener)(int x, int y));
        void unregisterMouseScrollListener(void (*listener)(int x, int y));

        void emitKeyDownEvent(int scanCode, int modifiers);
        void emitKeyDownEvent(int scanCode, int modifiers, void* extra);
        void registerKeyDownListener(void (*listener)(Snake::KeyStruct key));
        void unregisterKeyDownListener(void (*listener)(Snake::KeyStruct key));

        void emitKeyUpEvent(int scanCode, int modifiers);
        void emitKeyUpEvent(int scanCode, int modifiers, void* extra);
        void registerKeyUpListener(void (*listener)(Snake::KeyStruct key));
        void unregisterKeyUpListener(void (*listener)(Snake::KeyStruct key));

        void emitButtonDownEvent(int scanCode, int modifiers);
        void emitButtonDownEvent(int scanCode, int modifiers, void*);
        void registerButtonDownListener(void (*listener)(Snake::ButtonStruct button));
        void unregisterButtonDownListener(void (*listener)(Snake::ButtonStruct button));

        void emitButtonUpEvent(int scanCode, int modifiers);
        void emitButtonUpEvent(int scanCode, int modifiers, void*);
        void registerButtonUpListener(void (*listener)(Snake::ButtonStruct button));
        void unregisterButtonUpListener(void (*listener)(Snake::ButtonStruct button));
    };
};
#endif