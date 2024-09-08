#include "windowevents.hpp"

#include "keyboard.hpp"
#include "uuid.hpp"

#include <cstdlib>
#include <cstring>

#include <functional>
#include <map>
#include <vector>
#include <algorithm>

namespace Snake
{
    Snake::EventManager::EventManager()
    {
    }

    Snake::EventManager::~EventManager()
    {
    }

    void Snake::EventManager::emitWindowFocusEvent()
    {
        for (const auto& listenerEntry : this->windowFocusListeners)
        {
            listenerEntry.second();
        }
    }

    UUID* Snake::EventManager::registerWindowFocusListener(const WindowFocusListener& listener)
    {
        UUID* uuid = randomUuid();
        this->windowFocusListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterWindowFocusListener(UUID* uuid)
    {
        this->windowFocusListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitWindowUnfocusEvent()
    {
        for (const auto& listenerEntry : this->windowUnfocusListeners)
        {
            listenerEntry.second();
        }
    }

    UUID* Snake::EventManager::registerWindowUnfocusListener(const WindowUnfocusListener& listener)
    {
        UUID* uuid = randomUuid();
        this->windowUnfocusListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterWindowUnfocusListener(UUID* uuid)
    {
        this->windowUnfocusListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitWindowCloseEvent()
    {
        for (const auto& listenerEntry : this->windowCloseListeners)
        {
            listenerEntry.second();
        }
    }

    UUID* Snake::EventManager::registerWindowCloseListener(const WindowCloseListener& listener)
    {
        UUID* uuid = randomUuid();
        this->windowCloseListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterWindowCloseListener(UUID* uuid)
    {
        this->windowCloseListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitWindowMoveEvent(const signed int x, const signed int y)
    {
        for (const auto& listenerEntry : this->windowMoveListeners)
        {
            listenerEntry.second(x, y);
        }
    }

    UUID* Snake::EventManager::registerWindowMoveListener(const WindowMoveListener& listener)
    {
        UUID* uuid = randomUuid();
        this->windowMoveListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterWindowMoveListener(UUID* uuid)
    {
        this->windowMoveListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitWindowResizeEvent(const unsigned int width, const unsigned int height)
    {
        for (const auto& listenerEntry : this->windowResizeListeners)
        {
            listenerEntry.second(width, height);
        }
    }

    UUID* Snake::EventManager::registerWindowResizeListener(const WindowResizeListener& listener)
    {
        UUID* uuid = randomUuid();
        this->windowResizeListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterWindowResizeListener(UUID* uuid)
    {
        this->windowResizeListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitMouseMoveEvent(const signed int x, const signed int y)
    {
        for (const auto& listenerEntry : this->mouseMoveListeners)
        {
            listenerEntry.second(x, y);
        }
    }

    UUID* Snake::EventManager::registerMouseMoveListener(const MouseMoveListener& listener)
    {
        UUID* uuid = randomUuid();
        this->mouseMoveListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterMouseMoveListener(UUID* uuid)
    {
        this->mouseMoveListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitMouseScrollEvent(const signed int x, const signed int y)
    {
        for (const auto& listenerEntry : this->mouseScrollListeners)
        {
            listenerEntry.second(x, y);
        }
    }

    UUID* Snake::EventManager::registerMouseScrollListener(const MouseScrollListener& listener)
    {
        UUID* uuid = randomUuid();
        this->mouseScrollListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterMouseScrollListener(UUID* uuid)
    {
        this->mouseScrollListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitButtonDownEvent(const unsigned int scanCode, const unsigned int modifiers)
    {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitButtonDownEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra)
    {
        const Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, extra);

        for (const auto& listenerEntry : this->buttonDownListeners)
        {
            listenerEntry.second(button);
        }
    }

    UUID* Snake::EventManager::registerButtonDownListener(const ButtonDownListener& listener)
    {
        UUID* uuid = randomUuid();
        this->buttonDownListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterButtonDownListener(UUID* uuid)
    {
        this->buttonDownListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitButtonUpEvent(const unsigned int scanCode, const unsigned int modifiers)
    {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitButtonUpEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra)
    {
        const Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, extra);

        for (const auto& listenerEntry : this->buttonUpListeners)
        {
            listenerEntry.second(button);
        }
    }

    UUID* Snake::EventManager::registerButtonUpListener(const ButtonUpListener& listener)
    {
        UUID* uuid = randomUuid();
        this->buttonUpListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterButtonUpListener(UUID* uuid)
    {
        this->buttonUpListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitKeyDownEvent(const unsigned int scanCode, const unsigned int modifiers)
    {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitKeyDownEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra)
    {
        const Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, extra);

        for (const auto& listenerEntry : this->keyDownListeners)
        {
            listenerEntry.second(key);
        }
    }

    UUID* Snake::EventManager::registerKeyDownListener(const KeyDownListener& listener)
    {
        UUID* uuid = randomUuid();
        this->keyDownListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterKeyDownListener(UUID* uuid)
    {
        this->keyDownListeners.erase(uuid);
        deleteUuid(uuid);
    }

    void Snake::EventManager::emitKeyUpEvent(const unsigned int scanCode, const unsigned int modifiers)
    {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitKeyUpEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra)
    {
        const Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, extra);

        for (const auto& listenerEntry : this->keyUpListeners)
        {
            listenerEntry.second(key);
        }
    }

    UUID* Snake::EventManager::registerKeyUpListener(const KeyUpListener& listener)
    {
        UUID* uuid = randomUuid();
        this->keyUpListeners.insert(std::make_pair(uuid, listener));
        return uuid;
    }

    void Snake::EventManager::unregisterKeyUpListener(UUID* uuid)
    {
        this->keyUpListeners.erase(uuid);
        deleteUuid(uuid);
    }
};