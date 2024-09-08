#ifndef SNAKE_WINDOWEVENTSH
#define SNAKE_WINDOWEVENTSH

#include "keyboard.hpp"
#include "uuid.hpp"

#include <functional>
#include <map>
#include <vector>

namespace Snake
{
    typedef std::function<void()> WindowFocusListener;

    typedef std::function<void()> WindowUnfocusListener;
    typedef std::function<void()> WindowCloseListener;

    typedef std::function<void(const signed int x, const signed int y)> WindowMoveListener;
    typedef std::function<void(const unsigned int width, const unsigned int height)> WindowResizeListener;

    typedef std::function<void(const signed int x, const signed int y)> MouseMoveListener;
    typedef std::function<void(const signed int dx, const signed int dy)> MouseScrollListener;

    typedef std::function<void(const Snake::ButtonStruct button)> ButtonUpListener;
    typedef std::function<void(const Snake::ButtonStruct button)> ButtonDownListener;

    typedef std::function<void(const Snake::KeyStruct key)> KeyUpListener;
    typedef std::function<void(const Snake::KeyStruct key)> KeyDownListener;

    class EventManager
    {
    protected:
        std::map<UUID*, WindowFocusListener> windowFocusListeners;
        std::map<UUID*, WindowUnfocusListener> windowUnfocusListeners;
        std::map<UUID*, WindowCloseListener> windowCloseListeners;

        std::map<UUID*, WindowMoveListener> windowMoveListeners;
        std::map<UUID*, WindowResizeListener> windowResizeListeners;

        std::map<UUID*, MouseMoveListener> mouseMoveListeners;
        std::map<UUID*, MouseScrollListener> mouseScrollListeners;

        std::map<UUID*, ButtonDownListener> buttonDownListeners;
        std::map<UUID*, ButtonUpListener> buttonUpListeners;

        std::map<UUID*, KeyDownListener> keyDownListeners;
        std::map<UUID*, KeyUpListener> keyUpListeners;

    public:
        EventManager();
        ~EventManager();

        void emitWindowFocusEvent();
        UUID* registerWindowFocusListener(const WindowFocusListener& listener);
        void unregisterWindowFocusListener(UUID* uuid);

        void emitWindowUnfocusEvent();
        UUID* registerWindowUnfocusListener(const WindowUnfocusListener& listener);
        void unregisterWindowUnfocusListener(UUID* uuid);

        void emitWindowCloseEvent();
        UUID* registerWindowCloseListener(const WindowCloseListener& listener);
        void unregisterWindowCloseListener(UUID* uuid);

        void emitWindowMoveEvent(const signed int x, const signed int y);
        UUID* registerWindowMoveListener(const WindowMoveListener& listener);
        void unregisterWindowMoveListener(UUID* uuid);

        void emitWindowResizeEvent(const unsigned int width, const unsigned int height);
        UUID* registerWindowResizeListener(const WindowResizeListener& listener);
        void unregisterWindowResizeListener(UUID* uuid);

        void emitMouseMoveEvent(const signed int x, const signed int y);
        UUID* registerMouseMoveListener(const MouseMoveListener& listener);
        void unregisterMouseMoveListener(UUID* uuid);

        void emitMouseScrollEvent(const signed int dx, const signed int dy);
        UUID* registerMouseScrollListener(const MouseScrollListener& listener);
        void unregisterMouseScrollListener(UUID* uuid);

        void emitButtonDownEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitButtonDownEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        UUID* registerButtonDownListener(const ButtonDownListener& listener);
        void unregisterButtonDownListener(UUID* uuid);

        void emitButtonUpEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitButtonUpEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        UUID* registerButtonUpListener(const ButtonUpListener& listener);
        void unregisterButtonUpListener(UUID* uuid);

        void emitKeyDownEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitKeyDownEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        UUID* registerKeyDownListener(const KeyDownListener& listener);
        void unregisterKeyDownListener(UUID* uuid);

        void emitKeyUpEvent(const unsigned int scanCode, const unsigned int modifiers);
        void emitKeyUpEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
        UUID* registerKeyUpListener(const KeyUpListener& listener);
        void unregisterKeyUpListener(UUID* uuid);
    };
};
#endif