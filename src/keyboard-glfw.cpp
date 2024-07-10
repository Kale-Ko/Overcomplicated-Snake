#include "keyboard-common.cpp"

#include <GLFW/glfw3.h>

namespace Snake {
    const static std::map<const unsigned int, const Snake::Key_t> scanCodeToKeyCode = {
        { GLFW_KEY_A, Snake::Key::KEY_A },
        { GLFW_KEY_B, Snake::Key::KEY_B },
        { GLFW_KEY_C, Snake::Key::KEY_C },
        { GLFW_KEY_D, Snake::Key::KEY_D },
        { GLFW_KEY_E, Snake::Key::KEY_E },
        { GLFW_KEY_F, Snake::Key::KEY_F },
        { GLFW_KEY_G, Snake::Key::KEY_G },
        { GLFW_KEY_H, Snake::Key::KEY_H },
        { GLFW_KEY_I, Snake::Key::KEY_I },
        { GLFW_KEY_J, Snake::Key::KEY_J },
        { GLFW_KEY_K, Snake::Key::KEY_K },
        { GLFW_KEY_L, Snake::Key::KEY_L },
        { GLFW_KEY_M, Snake::Key::KEY_M },
        { GLFW_KEY_N, Snake::Key::KEY_N },
        { GLFW_KEY_O, Snake::Key::KEY_O },
        { GLFW_KEY_P, Snake::Key::KEY_P },
        { GLFW_KEY_Q, Snake::Key::KEY_Q },
        { GLFW_KEY_R, Snake::Key::KEY_R },
        { GLFW_KEY_S, Snake::Key::KEY_S },
        { GLFW_KEY_T, Snake::Key::KEY_T },
        { GLFW_KEY_U, Snake::Key::KEY_U },
        { GLFW_KEY_V, Snake::Key::KEY_V },
        { GLFW_KEY_W, Snake::Key::KEY_W },
        { GLFW_KEY_X, Snake::Key::KEY_X },
        { GLFW_KEY_Y, Snake::Key::KEY_Y },
        { GLFW_KEY_Z, Snake::Key::KEY_Z },

        { GLFW_KEY_0, Snake::Key::KEY_0 },
        { GLFW_KEY_1, Snake::Key::KEY_1 },
        { GLFW_KEY_2, Snake::Key::KEY_2 },
        { GLFW_KEY_3, Snake::Key::KEY_3 },
        { GLFW_KEY_4, Snake::Key::KEY_4 },
        { GLFW_KEY_5, Snake::Key::KEY_5 },
        { GLFW_KEY_6, Snake::Key::KEY_6 },
        { GLFW_KEY_7, Snake::Key::KEY_7 },
        { GLFW_KEY_8, Snake::Key::KEY_8 },
        { GLFW_KEY_9, Snake::Key::KEY_9 },

        { GLFW_KEY_COMMA, Snake::Key::KEY_COMMA },
        { GLFW_KEY_PERIOD, Snake::Key::KEY_PERIOD },
        { GLFW_KEY_SLASH, Snake::Key::KEY_SLASH },
        { GLFW_KEY_SEMICOLON, Snake::Key::KEY_SEMI_COLON },
        { GLFW_KEY_APOSTROPHE, Snake::Key::KEY_APOSTROPHE },
        { GLFW_KEY_LEFT_BRACKET, Snake::Key::KEY_OPEN_BRACKETS },
        { GLFW_KEY_RIGHT_BRACKET, Snake::Key::KEY_CLOSE_BRACKETS },
        { GLFW_KEY_BACKSLASH, Snake::Key::KEY_BACK_SLASH },
        { GLFW_KEY_MINUS, Snake::Key::KEY_MINUS },
        { GLFW_KEY_EQUAL, Snake::Key::KEY_EQUALS },
        { GLFW_KEY_GRAVE_ACCENT, Snake::Key::KEY_GRAVE },

        { GLFW_KEY_SPACE, Snake::Key::KEY_SPACE },
        { GLFW_KEY_ENTER, Snake::Key::KEY_ENTER },
        { GLFW_KEY_BACKSPACE, Snake::Key::KEY_BACKSPACE },
        { GLFW_KEY_TAB, Snake::Key::KEY_TAB },
        { GLFW_KEY_ESCAPE, Snake::Key::KEY_ESCAPE },

        { GLFW_KEY_F1, Snake::Key::KEY_F1 },
        { GLFW_KEY_F2, Snake::Key::KEY_F2 },
        { GLFW_KEY_F3, Snake::Key::KEY_F3 },
        { GLFW_KEY_F4, Snake::Key::KEY_F4 },
        { GLFW_KEY_F5, Snake::Key::KEY_F5 },
        { GLFW_KEY_F6, Snake::Key::KEY_F6 },
        { GLFW_KEY_F7, Snake::Key::KEY_F7 },
        { GLFW_KEY_F8, Snake::Key::KEY_F8 },
        { GLFW_KEY_F9, Snake::Key::KEY_F9 },
        { GLFW_KEY_F10, Snake::Key::KEY_F10 },
        { GLFW_KEY_F11, Snake::Key::KEY_F11 },
        { GLFW_KEY_F12, Snake::Key::KEY_F12 },

        { GLFW_KEY_LEFT_SHIFT, Snake::Key::KEY_SHIFT },
        { GLFW_KEY_RIGHT_SHIFT, Snake::Key::KEY_SHIFT },
        { GLFW_KEY_LEFT_CONTROL, Snake::Key::KEY_CONTROL },
        { GLFW_KEY_RIGHT_CONTROL, Snake::Key::KEY_CONTROL },
        { GLFW_KEY_LEFT_ALT, Snake::Key::KEY_ALT },
        { GLFW_KEY_RIGHT_ALT, Snake::Key::KEY_ALT },
        { GLFW_KEY_LEFT_SUPER, Snake::Key::KEY_META },
        { GLFW_KEY_RIGHT_SUPER, Snake::Key::KEY_META },
        { GLFW_KEY_CAPS_LOCK, Snake::Key::KEY_CAPS_LOCK }
    };
    const static std::map<const unsigned int, const Snake::Button_t> scanCodeToButtonCode = {
        { GLFW_MOUSE_BUTTON_LEFT, Snake::Button::BUTTON_LEFT },
        { GLFW_MOUSE_BUTTON_RIGHT, Snake::Button::BUTTON_RIGHT },
        { GLFW_MOUSE_BUTTON_MIDDLE, Snake::Button::BUTTON_MIDDLE },

        { GLFW_MOUSE_BUTTON_4, Snake::Button::BUTTON_EXTRA1 },
        { GLFW_MOUSE_BUTTON_5, Snake::Button::BUTTON_EXTRA2 },
        { GLFW_MOUSE_BUTTON_6, Snake::Button::BUTTON_EXTRA3 },
        { GLFW_MOUSE_BUTTON_7, Snake::Button::BUTTON_EXTRA4 },
        { GLFW_MOUSE_BUTTON_8, Snake::Button::BUTTON_EXTRA5 }
    };

    const Snake::KeyStruct getKeyFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        Snake::Key_t key;
        if (scanCodeToKeyCode.contains(scanCode)) {
            key = scanCodeToKeyCode.at(scanCode);
        }
        else {
            key = Snake::Key::KEY_UNKOWN;
        }

        Snake::KeyMod_t keyMods = 0x00;
        if ((modifiers & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT) {
            keyMods |= Snake::KeyMod::MOD_SHIFT;
        }
        if ((modifiers & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL) {
            keyMods |= Snake::KeyMod::MOD_CONTROL;
        }
        if ((modifiers & GLFW_MOD_ALT) == GLFW_MOD_ALT) {
            keyMods |= Snake::KeyMod::MOD_ALT;
        }
        if ((modifiers & GLFW_MOD_SUPER) == GLFW_MOD_SUPER) {
            keyMods |= Snake::KeyMod::MOD_META;
        }
        if ((modifiers & GLFW_MOD_CAPS_LOCK) == GLFW_MOD_CAPS_LOCK) {
            keyMods |= Snake::KeyMod::MOD_CAPS_LOCK;
        }

        std::string string = getStringFromKeyCode(key, keyMods);

        return KeyStruct{ .scanCode = scanCode, .code = key, .modifiers = keyMods, .string = string };
    }

    const Snake::ButtonStruct getButtonFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        Snake::Button_t button;
        if (scanCodeToButtonCode.contains(scanCode)) {
            button = scanCodeToButtonCode.at(scanCode);
        }
        else {
            button = Snake::Button::BUTTON_UNKOWN;
        }

        Snake::KeyMod_t buttonMods = 0x00;
        if ((modifiers & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT) {
            buttonMods |= Snake::KeyMod::MOD_SHIFT;
        }
        if ((modifiers & GLFW_MOD_CONTROL) == GLFW_MOD_CONTROL) {
            buttonMods |= Snake::KeyMod::MOD_CONTROL;
        }
        if ((modifiers & GLFW_MOD_ALT) == GLFW_MOD_ALT) {
            buttonMods |= Snake::KeyMod::MOD_ALT;
        }
        if ((modifiers & GLFW_MOD_SUPER) == GLFW_MOD_SUPER) {
            buttonMods |= Snake::KeyMod::MOD_META;
        }
        if ((modifiers & GLFW_MOD_CAPS_LOCK) == GLFW_MOD_CAPS_LOCK) {
            buttonMods |= Snake::KeyMod::MOD_CAPS_LOCK;
        }

        return ButtonStruct{ .scanCode = scanCode, .code = button, .modifiers = buttonMods };
    }
};