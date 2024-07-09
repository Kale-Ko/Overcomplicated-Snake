#include "keyboard-common.cpp"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

namespace Snake {
    const static std::map<const unsigned int, const Snake::Key_t> scanCodeToKeyCode = {
        { XK_a, Snake::Key::KEY_A },
        { XK_b, Snake::Key::KEY_B },
        { XK_c, Snake::Key::KEY_C },
        { XK_d, Snake::Key::KEY_D },
        { XK_e, Snake::Key::KEY_E },
        { XK_f, Snake::Key::KEY_F },
        { XK_g, Snake::Key::KEY_G },
        { XK_h, Snake::Key::KEY_H },
        { XK_i, Snake::Key::KEY_I },
        { XK_j, Snake::Key::KEY_J },
        { XK_k, Snake::Key::KEY_K },
        { XK_l, Snake::Key::KEY_L },
        { XK_m, Snake::Key::KEY_M },
        { XK_n, Snake::Key::KEY_N },
        { XK_o, Snake::Key::KEY_O },
        { XK_p, Snake::Key::KEY_P },
        { XK_q, Snake::Key::KEY_Q },
        { XK_r, Snake::Key::KEY_R },
        { XK_s, Snake::Key::KEY_S },
        { XK_t, Snake::Key::KEY_T },
        { XK_u, Snake::Key::KEY_U },
        { XK_v, Snake::Key::KEY_V },
        { XK_w, Snake::Key::KEY_W },
        { XK_x, Snake::Key::KEY_X },
        { XK_y, Snake::Key::KEY_Y },
        { XK_z, Snake::Key::KEY_Z },

        { XK_0, Snake::Key::KEY_0 },
        { XK_1, Snake::Key::KEY_1 },
        { XK_2, Snake::Key::KEY_2 },
        { XK_3, Snake::Key::KEY_3 },
        { XK_4, Snake::Key::KEY_4 },
        { XK_5, Snake::Key::KEY_5 },
        { XK_6, Snake::Key::KEY_6 },
        { XK_7, Snake::Key::KEY_7 },
        { XK_8, Snake::Key::KEY_8 },
        { XK_9, Snake::Key::KEY_9 },

        { XK_comma, Snake::Key::KEY_COMMA },
        { XK_period, Snake::Key::KEY_PERIOD },
        { XK_slash, Snake::Key::KEY_SLASH },
        { XK_semicolon, Snake::Key::KEY_SEMI_COLON },
        { XK_apostrophe, Snake::Key::KEY_APOSTROPHE },
        { XK_bracketleft, Snake::Key::KEY_OPEN_BRACKETS },
        { XK_bracketright, Snake::Key::KEY_CLOSE_BRACKETS },
        { XK_backslash, Snake::Key::KEY_BACK_SLASH },
        { XK_minus, Snake::Key::KEY_MINUS },
        { XK_equal, Snake::Key::KEY_EQUALS },
        { XK_grave, Snake::Key::KEY_GRAVE },

        { XK_space, Snake::Key::KEY_SPACE },
        { XK_Return, Snake::Key::KEY_ENTER },
        { XK_BackSpace, Snake::Key::KEY_BACKSPACE },
        { XK_Tab, Snake::Key::KEY_TAB },
        { XK_Escape, Snake::Key::KEY_ESCAPE },

        { XK_F1, Snake::Key::KEY_F1 },
        { XK_F2, Snake::Key::KEY_F2 },
        { XK_F3, Snake::Key::KEY_F3 },
        { XK_F4, Snake::Key::KEY_F4 },
        { XK_F5, Snake::Key::KEY_F5 },
        { XK_F6, Snake::Key::KEY_F6 },
        { XK_F7, Snake::Key::KEY_F7 },
        { XK_F8, Snake::Key::KEY_F8 },
        { XK_F9, Snake::Key::KEY_F9 },
        { XK_F10, Snake::Key::KEY_F10 },
        { XK_F11, Snake::Key::KEY_F11 },
        { XK_F12, Snake::Key::KEY_F12 },

        { XK_Shift_L, Snake::Key::KEY_SHIFT },
        { XK_Shift_R, Snake::Key::KEY_SHIFT },
        { XK_Control_L, Snake::Key::KEY_CONTROL },
        { XK_Control_R, Snake::Key::KEY_CONTROL },
        { XK_Alt_L, Snake::Key::KEY_ALT },
        { XK_Alt_R, Snake::Key::KEY_ALT },
        { XK_Super_L, Snake::Key::KEY_META },
        { XK_Super_R, Snake::Key::KEY_META },
        { XK_Caps_Lock, Snake::Key::KEY_CAPS_LOCK }
    };
    const static std::map<const unsigned int, const Snake::Button_t> scanCodeToButtonCode = {
        { 0x01, Snake::Button::BUTTON_LEFT },
        { 0x03, Snake::Button::BUTTON_RIGHT },
        { 0x02, Snake::Button::BUTTON_MIDDLE },

        { 0x04, Snake::Button::BUTTON_EXTRA1 },
        { 0x05, Snake::Button::BUTTON_EXTRA2 },
        { 0x06, Snake::Button::BUTTON_EXTRA3 },
        { 0x07, Snake::Button::BUTTON_EXTRA4 },
        { 0x08, Snake::Button::BUTTON_EXTRA5 }
    };

    const Snake::KeyStruct getKeyFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra) {
        unsigned int scanCodeSym = XLookupKeysym((XKeyEvent*)extra, 0);

        Snake::Key_t key;
        if (scanCodeToKeyCode.contains(scanCodeSym)) {
            key = scanCodeToKeyCode.at(scanCodeSym);
        }
        else {
            key = Snake::Key::KEY_UNKOWN;
        }

        Snake::KeyMod_t keyMods = 0x00;
        if ((modifiers & 0x01) == 0x01) {
            keyMods |= Snake::KeyMod::MOD_SHIFT;
        }
        if ((modifiers & 0x04) == 0x04) {
            keyMods |= Snake::KeyMod::MOD_CONTROL;
        }
        if ((modifiers & 0x08) == 0x08) {
            keyMods |= Snake::KeyMod::MOD_ALT;
        }
        if ((modifiers & 0x40) == 0x40) {
            keyMods |= Snake::KeyMod::MOD_META;
        }
        if ((modifiers & 0x02) == 0x02) {
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
        if ((modifiers & 0x01) == 0x01) {
            buttonMods |= Snake::KeyMod::MOD_SHIFT;
        }
        if ((modifiers & 0x04) == 0x04) {
            buttonMods |= Snake::KeyMod::MOD_CONTROL;
        }
        if ((modifiers & 0x08) == 0x08) {
            buttonMods |= Snake::KeyMod::MOD_ALT;
        }
        if ((modifiers & 0x40) == 0x40) {
            buttonMods |= Snake::KeyMod::MOD_META;
        }
        if ((modifiers & 0x02) == 0x02) {
            buttonMods |= Snake::KeyMod::MOD_CAPS_LOCK;
        }

        return ButtonStruct{ .scanCode = scanCode, .code = button, .modifiers = buttonMods };
    }
};