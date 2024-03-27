#include "windowevents.hpp"

#include "keyboard.hpp"

#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

namespace Snake {
    Snake::EventManager::EventManager()
    {
    }

    Snake::EventManager::~EventManager()
    {
    }

    void Snake::EventManager::emitWindowFocusEvent()
    {
        for (void (*listener)() : this->windowFocusListeners)
        {
            listener();
        }
    }

    void Snake::EventManager::registerWindowFocusListener(void (*listener)())
    {
        this->windowFocusListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterWindowFocusListener(void (*listener)())
    {
        this->windowFocusListeners.erase(std::remove(this->windowFocusListeners.begin(), this->windowFocusListeners.end(), listener), this->windowFocusListeners.end());
    }

    void Snake::EventManager::emitWindowUnfocusEvent()
    {
        for (void (*listener)() : this->windowUnfocusListeners)
        {
            listener();
        }
    }

    void Snake::EventManager::registerWindowUnfocusListener(void (*listener)())
    {
        this->windowUnfocusListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterWindowUnfocusListener(void (*listener)())
    {
        this->windowUnfocusListeners.erase(std::remove(this->windowUnfocusListeners.begin(), this->windowUnfocusListeners.end(), listener), this->windowUnfocusListeners.end());
    }

    void Snake::EventManager::emitWindowResizeEvent(int width, int height)
    {
        for (void (*listener)(int width, int height) : this->windowResizeListeners)
        {
            listener(width, height);
        }
    }

    void Snake::EventManager::registerWindowResizeListener(void (*listener)(int width, int height))
    {
        this->windowResizeListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterWindowResizeListener(void (*listener)(int width, int height))
    {
        this->windowResizeListeners.erase(std::remove(this->windowResizeListeners.begin(), this->windowResizeListeners.end(), listener), this->windowResizeListeners.end());
    }

    void Snake::EventManager::emitMouseMoveEvent(int x, int y)
    {
        for (void (*listener)(int x, int y) : this->mouseMoveListeners)
        {
            listener(x, y);
        }
    }

    void Snake::EventManager::registerMouseMoveListener(void (*listener)(int x, int y))
    {
        this->mouseMoveListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterMouseMoveListener(void (*listener)(int x, int y))
    {
        this->mouseMoveListeners.erase(std::remove(this->mouseMoveListeners.begin(), this->mouseMoveListeners.end(), listener), this->mouseMoveListeners.end());
    }

    void Snake::EventManager::emitMouseScrollEvent(int x, int y)
    {
        for (void (*listener)(int x, int y) : this->mouseScrollListeners)
        {
            listener(x, y);
        }
    }

    void Snake::EventManager::registerMouseScrollListener(void (*listener)(int x, int y))
    {
        this->mouseScrollListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterMouseScrollListener(void (*listener)(int x, int y))
    {
        this->mouseScrollListeners.erase(std::remove(this->mouseScrollListeners.begin(), this->mouseScrollListeners.end(), listener), this->mouseScrollListeners.end());
    }

    void Snake::EventManager::emitKeyDownEvent(int scanCode, int modifiers)
    {
        Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, NULL);

        for (void (*listener)(Snake::KeyStruct key) : this->keyDownListeners)
        {
            listener(key);
        }
    }

    void Snake::EventManager::emitKeyDownEvent(int scanCode, int modifiers, void* extra)
    {
        Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(Snake::KeyStruct key) : this->keyDownListeners)
        {
            listener(key);
        }
    }

    void Snake::EventManager::registerKeyDownListener(void (*listener)(Snake::KeyStruct key))
    {
        this->keyDownListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterKeyDownListener(void (*listener)(Snake::KeyStruct key))
    {
        this->keyDownListeners.erase(std::remove(this->keyDownListeners.begin(), this->keyDownListeners.end(), listener), this->keyDownListeners.end());
    }

    void Snake::EventManager::emitKeyUpEvent(int scanCode, int modifiers)
    {
        Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, NULL);

        for (void (*listener)(Snake::KeyStruct key) : this->keyUpListeners)
        {
            listener(key);
        }
    }

    void Snake::EventManager::emitKeyUpEvent(int scanCode, int modifiers, void* extra)
    {
        Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(Snake::KeyStruct key) : this->keyUpListeners)
        {
            listener(key);
        }
    }

    void Snake::EventManager::registerKeyUpListener(void (*listener)(Snake::KeyStruct key))
    {
        this->keyUpListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterKeyUpListener(void (*listener)(Snake::KeyStruct key))
    {
        this->keyUpListeners.erase(std::remove(this->keyUpListeners.begin(), this->keyUpListeners.end(), listener), this->keyUpListeners.end());
    }

    void Snake::EventManager::emitButtonDownEvent(int scanCode, int modifiers)
    {
        Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, NULL);

        for (void (*listener)(Snake::ButtonStruct button) : this->buttonDownListeners)
        {
            listener(button);
        }
    }

    void Snake::EventManager::emitButtonDownEvent(int scanCode, int modifiers, void* extra)
    {
        Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(Snake::ButtonStruct button) : this->buttonDownListeners)
        {
            listener(button);
        }
    }

    void Snake::EventManager::registerButtonDownListener(void (*listener)(Snake::ButtonStruct button))
    {
        this->buttonDownListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterButtonDownListener(void (*listener)(Snake::ButtonStruct button))
    {
        this->buttonDownListeners.erase(std::remove(this->buttonDownListeners.begin(), this->buttonDownListeners.end(), listener), this->buttonDownListeners.end());
    }

    void Snake::EventManager::emitButtonUpEvent(int scanCode, int modifiers)
    {
        Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, NULL);

        for (void (*listener)(Snake::ButtonStruct button) : this->buttonUpListeners)
        {
            listener(button);
        }
    }

    void Snake::EventManager::emitButtonUpEvent(int scanCode, int modifiers, void* extra)
    {
        Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(Snake::ButtonStruct button) : this->buttonUpListeners)
        {
            listener(button);
        }
    }

    void Snake::EventManager::registerButtonUpListener(void (*listener)(Snake::ButtonStruct button))
    {
        this->buttonUpListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterButtonUpListener(void (*listener)(Snake::ButtonStruct button))
    {
        this->buttonUpListeners.erase(std::remove(this->buttonUpListeners.begin(), this->buttonUpListeners.end(), listener), this->buttonUpListeners.end());
    }
};