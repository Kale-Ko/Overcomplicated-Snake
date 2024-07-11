#ifndef SNAKE_WINDOWEVENTSH
#define SNAKE_WINDOWEVENTSH

#include "keyboard.hpp"

#include <vector>

namespace Snake {
    class EventManager {
    protected:
        std::vector<void (*)()> windowFocusListeners;
        std::vector<void (*)()> windowUnfocusListeners;
        std::vector<void (*)()> windowCloseListeners;

        std::vector<void (*)(const signed int x, const signed int y)> windowMoveListeners;
        std::vector<void (*)(const unsigned int width, const unsigned int height)> windowResizeListeners;

        std::vector<void (*)(const signed int x, const signed int y)> mouseMoveListeners;
        std::vector<void (*)(const signed int x, const signed int y)> mouseScrollListeners;

        std::vector<void (*)(const Snake::ButtonStruct button)> buttonPressListeners;
        std::vector<void (*)(const Snake::ButtonStruct button)> buttonDownListeners;
        std::vector<void (*)(const Snake::ButtonStruct button)> buttonUpListeners;

        std::vector<void (*)(const Snake::KeyStruct key)> keyPressListeners;
        std::vector<void (*)(const Snake::KeyStruct key)> keyDownListeners;
        std::vector<void (*)(const Snake::KeyStruct key)> keyUpListeners;

    public:
        EventManager();
        ~EventManager();

        void emitWindowFocusEvent();
        void registerWindowFocusListener(void (*listener)());
        void unregisterWindowFocusListener(void (*listener)());

        void emitWindowUnfocusEvent();
        void registerWindowUnfocusListener(void (*listener)());
        void unregisterWindowUnfocusListener(void (*listener)());

        void emitWindowCloseEvent();
        void registerWindowCloseListener(void (*listener)());
        void unregisterWindowCloseListener(void (*listener)());

        void emitWindowMoveEvent(const signed int x, const signed int y);
        void registerWindowMoveListener(void (*listener)(const signed int x, const signed int y));
        void unregisterWindowMoveListener(void (*listener)(const signed int x, const signed int y));

        void emitWindowResizeEvent(const unsigned int width, const unsigned int height);
        void registerWindowResizeListener(void (*listener)(const unsigned int width, const unsigned int height));
        void unregisterWindowResizeListener(void (*listener)(const unsigned int width, const unsigned int height));

        void emitMouseMoveEvent(const signed int x, const signed int y);
        void registerMouseMoveListener(void (*listener)(const signed int x, const signed int y));
        void unregisterMouseMoveListener(void (*listener)(const signed int x, const signed int y));

        void emitMouseScrollEvent(const signed int x, const signed int y);
        void registerMouseScrollListener(void (*listener)(const signed int x, const signed int y));
        void unregisterMouseScrollListener(void (*listener)(const signed int x, const signed int y));

        void emitButtonPressEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitButtonPressEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        void registerButtonPressListener(void (*listener)(const Snake::ButtonStruct button));
        void unregisterButtonPressListener(void (*listener)(const Snake::ButtonStruct button));

        void emitButtonDownEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitButtonDownEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        void registerButtonDownListener(void (*listener)(const Snake::ButtonStruct button));
        void unregisterButtonDownListener(void (*listener)(const Snake::ButtonStruct button));

        void emitButtonUpEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitButtonUpEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        void registerButtonUpListener(void (*listener)(const Snake::ButtonStruct button));
        void unregisterButtonUpListener(void (*listener)(const Snake::ButtonStruct button));

        void emitKeyPressEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitKeyPressEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        void registerKeyPressListener(void (*listener)(const Snake::KeyStruct key));
        void unregisterKeyPressListener(void (*listener)(const Snake::KeyStruct key));

        void emitKeyDownEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitKeyDownEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        void registerKeyDownListener(void (*listener)(const Snake::KeyStruct key));
        void unregisterKeyDownListener(void (*listener)(const Snake::KeyStruct key));

        void emitKeyUpEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitKeyUpEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        void registerKeyUpListener(void (*listener)(const Snake::KeyStruct key));
        void unregisterKeyUpListener(void (*listener)(const Snake::KeyStruct key));
    };
};
#endif