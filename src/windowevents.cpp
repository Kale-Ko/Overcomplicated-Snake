#include "windowevents.hpp"

#include "keyboard.hpp"

#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

namespace Snake {
    Snake::EventManager::EventManager() {
    }

    Snake::EventManager::~EventManager() {
    }

    void Snake::EventManager::emitWindowFocusEvent() {
        for (void (*listener)() : this->windowFocusListeners) {
            listener();
        }
    }

    void Snake::EventManager::registerWindowFocusListener(void (*listener)()) {
        this->windowFocusListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterWindowFocusListener(void (*listener)()) {
        this->windowFocusListeners.erase(std::remove(this->windowFocusListeners.begin(), this->windowFocusListeners.end(), listener), this->windowFocusListeners.end());
    }

    void Snake::EventManager::emitWindowUnfocusEvent() {
        for (void (*listener)() : this->windowUnfocusListeners) {
            listener();
        }
    }

    void Snake::EventManager::registerWindowUnfocusListener(void (*listener)()) {
        this->windowUnfocusListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterWindowUnfocusListener(void (*listener)()) {
        this->windowUnfocusListeners.erase(std::remove(this->windowUnfocusListeners.begin(), this->windowUnfocusListeners.end(), listener), this->windowUnfocusListeners.end());
    }

    void Snake::EventManager::emitWindowCloseEvent() {
        for (void (*listener)() : this->windowCloseListeners) {
            listener();
        }
    }

    void Snake::EventManager::registerWindowCloseListener(void (*listener)()) {
        this->windowCloseListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterWindowCloseListener(void (*listener)()) {
        this->windowCloseListeners.erase(std::remove(this->windowCloseListeners.begin(), this->windowCloseListeners.end(), listener), this->windowCloseListeners.end());
    }

    void Snake::EventManager::emitWindowMoveEvent(const signed int x, const signed int y) {
        for (void (*listener)(const signed int x, const signed int y) : this->windowMoveListeners) {
            listener(x, y);
        }
    }

    void Snake::EventManager::registerWindowMoveListener(void (*listener)(const signed int x, const signed int y)) {
        this->windowMoveListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterWindowMoveListener(void (*listener)(const signed int x, const signed int y)) {
        this->windowMoveListeners.erase(std::remove(this->windowMoveListeners.begin(), this->windowMoveListeners.end(), listener), this->windowMoveListeners.end());
    }

    void Snake::EventManager::emitWindowResizeEvent(const unsigned int width, const unsigned int height) {
        for (void (*listener)(const unsigned int width, const unsigned int height) : this->windowResizeListeners) {
            listener(width, height);
        }
    }

    void Snake::EventManager::registerWindowResizeListener(void (*listener)(const unsigned int width, const unsigned int height)) {
        this->windowResizeListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterWindowResizeListener(void (*listener)(const unsigned int width, const unsigned int height)) {
        this->windowResizeListeners.erase(std::remove(this->windowResizeListeners.begin(), this->windowResizeListeners.end(), listener), this->windowResizeListeners.end());
    }

    void Snake::EventManager::emitMouseMoveEvent(const signed int x, const signed int y) {
        for (void (*listener)(const signed int x, const signed int y) : this->mouseMoveListeners) {
            listener(x, y);
        }
    }

    void Snake::EventManager::registerMouseMoveListener(void (*listener)(const signed int x, const signed int y)) {
        this->mouseMoveListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterMouseMoveListener(void (*listener)(const signed int x, const signed int y)) {
        this->mouseMoveListeners.erase(std::remove(this->mouseMoveListeners.begin(), this->mouseMoveListeners.end(), listener), this->mouseMoveListeners.end());
    }

    void Snake::EventManager::emitMouseScrollEvent(const signed int x, const signed int y) {
        for (void (*listener)(const signed int x, const signed int y) : this->mouseScrollListeners) {
            listener(x, y);
        }
    }

    void Snake::EventManager::registerMouseScrollListener(void (*listener)(const signed int x, const signed int y)) {
        this->mouseScrollListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterMouseScrollListener(void (*listener)(const signed int x, const signed int y)) {
        this->mouseScrollListeners.erase(std::remove(this->mouseScrollListeners.begin(), this->mouseScrollListeners.end(), listener), this->mouseScrollListeners.end());
    }

    void Snake::EventManager::emitButtonPressEvent(const unsigned int scanCode, const unsigned int modifiers) {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitButtonPressEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        const Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(const Snake::ButtonStruct button) : this->buttonPressListeners) {
            listener(button);
        }
    }

    void Snake::EventManager::registerButtonPressListener(void (*listener)(const Snake::ButtonStruct button)) {
        this->buttonPressListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterButtonPressListener(void (*listener)(const Snake::ButtonStruct button)) {
        this->buttonPressListeners.erase(std::remove(this->buttonPressListeners.begin(), this->buttonPressListeners.end(), listener), this->buttonPressListeners.end());
    }

    void Snake::EventManager::emitButtonDownEvent(const unsigned int scanCode, const unsigned int modifiers) {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitButtonDownEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        const Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(const Snake::ButtonStruct button) : this->buttonDownListeners) {
            listener(button);
        }
    }

    void Snake::EventManager::registerButtonDownListener(void (*listener)(const Snake::ButtonStruct button)) {
        this->buttonDownListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterButtonDownListener(void (*listener)(const Snake::ButtonStruct button)) {
        this->buttonDownListeners.erase(std::remove(this->buttonDownListeners.begin(), this->buttonDownListeners.end(), listener), this->buttonDownListeners.end());
    }

    void Snake::EventManager::emitButtonUpEvent(const unsigned int scanCode, const unsigned int modifiers) {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitButtonUpEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        const Snake::ButtonStruct button = Snake::getButtonFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(const Snake::ButtonStruct button) : this->buttonUpListeners) {
            listener(button);
        }
    }

    void Snake::EventManager::registerButtonUpListener(void (*listener)(const Snake::ButtonStruct button)) {
        this->buttonUpListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterButtonUpListener(void (*listener)(const Snake::ButtonStruct button)) {
        this->buttonUpListeners.erase(std::remove(this->buttonUpListeners.begin(), this->buttonUpListeners.end(), listener), this->buttonUpListeners.end());
    }

    void Snake::EventManager::emitKeyPressEvent(const unsigned int scanCode, const unsigned int modifiers) {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitKeyPressEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        const Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(const Snake::KeyStruct key) : this->keyPressListeners) {
            listener(key);
        }
    }

    void Snake::EventManager::registerKeyPressListener(void (*listener)(const Snake::KeyStruct key)) {
        this->keyPressListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterKeyPressListener(void (*listener)(const Snake::KeyStruct key)) {
        this->keyPressListeners.erase(std::remove(this->keyPressListeners.begin(), this->keyPressListeners.end(), listener), this->keyPressListeners.end());
    }

    void Snake::EventManager::emitKeyDownEvent(const unsigned int scanCode, const unsigned int modifiers) {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitKeyDownEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        const Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(const Snake::KeyStruct key) : this->keyDownListeners) {
            listener(key);
        }
    }

    void Snake::EventManager::registerKeyDownListener(void (*listener)(const Snake::KeyStruct key)) {
        this->keyDownListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterKeyDownListener(void (*listener)(const Snake::KeyStruct key)) {
        this->keyDownListeners.erase(std::remove(this->keyDownListeners.begin(), this->keyDownListeners.end(), listener), this->keyDownListeners.end());
    }

    void Snake::EventManager::emitKeyUpEvent(const unsigned int scanCode, const unsigned int modifiers) {
        throw "Unimplemented";
    }

    void Snake::EventManager::emitKeyUpEvent(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        const Snake::KeyStruct key = Snake::getKeyFromScanCode(scanCode, modifiers, extra);

        for (void (*listener)(const Snake::KeyStruct key) : this->keyUpListeners) {
            listener(key);
        }
    }

    void Snake::EventManager::registerKeyUpListener(void (*listener)(const Snake::KeyStruct key)) {
        this->keyUpListeners.push_back(listener);
    }

    void Snake::EventManager::unregisterKeyUpListener(void (*listener)(const Snake::KeyStruct key)) {
        this->keyUpListeners.erase(std::remove(this->keyUpListeners.begin(), this->keyUpListeners.end(), listener), this->keyUpListeners.end());
    }
};