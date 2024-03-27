#ifndef SNAKE_KEYBOARDH
#define SNAKE_KEYBOARDH

#include <string>

namespace Snake {
    namespace KeyMod {
        static int MOD_SHIFT = 0x01;
        static int MOD_CONTROL = 0x02;
        static int MOD_ALT = 0x04;
        static int MOD_META = 0x08;
        static int MOD_CAPS_LOCK = 0x10;
    };

    enum Key {
        KEY_A = 0x00,
        KEY_B = 0x01,
        KEY_C = 0x02,
        KEY_D = 0x03,
        KEY_E = 0x04,
        KEY_F = 0x05,
        KEY_G = 0x06,
        KEY_H = 0x07,
        KEY_I = 0x08,
        KEY_J = 0x09,
        KEY_K = 0x0A,
        KEY_L = 0x0B,
        KEY_M = 0x0C,
        KEY_N = 0x0D,
        KEY_O = 0x0E,
        KEY_P = 0x0F,
        KEY_Q = 0x10,
        KEY_R = 0x11,
        KEY_S = 0x12,
        KEY_T = 0x13,
        KEY_U = 0x14,
        KEY_V = 0x15,
        KEY_W = 0x16,
        KEY_X = 0x17,
        KEY_Y = 0x18,
        KEY_Z = 0x19,

        KEY_0 = 0x20,
        KEY_1 = 0x21,
        KEY_2 = 0x22,
        KEY_3 = 0x23,
        KEY_4 = 0x24,
        KEY_5 = 0x25,
        KEY_6 = 0x26,
        KEY_7 = 0x27,
        KEY_8 = 0x28,
        KEY_9 = 0x29,

        KEY_COMMA = 0x30,
        KEY_PERIOD = 0x31,
        KEY_SLASH = 0x32,
        KEY_SEMI_COLON = 0x33,
        KEY_APOSTROPHE = 0x34,
        KEY_OPEN_BRACKETS = 0x35,
        KEY_CLOSE_BRACKETS = 0x36,
        KEY_BACK_SLASH = 0x37,
        KEY_MINUS = 0x38,
        KEY_EQUALS = 0x39,
        KEY_GRAVE = 0x3A,

        KEY_SPACE = 0x40,
        KEY_ENTER = 0x41,
        KEY_BACKSPACE = 0x42,
        KEY_TAB = 0x43,
        KEY_ESCAPE = 0x44,

        KEY_F1 = 0x50,
        KEY_F2 = 0x51,
        KEY_F3 = 0x52,
        KEY_F4 = 0x53,
        KEY_F5 = 0x54,
        KEY_F6 = 0x55,
        KEY_F7 = 0x56,
        KEY_F8 = 0x57,
        KEY_F9 = 0x58,
        KEY_F10 = 0x59,
        KEY_F11 = 0x5A,
        KEY_F12 = 0x5B,

        KEY_SHIFT = 0x60,
        KEY_CONTROL = 0x61,
        KEY_ALT = 0x62,
        KEY_CAPS_LOCK = 0x63,
        KEY_META = 0x64,

        KEY_UNKOWN = 0xFF
    };

    enum Button {
        BUTTON_LEFT = 0x00,
        BUTTON_RIGHT = 0x01,
        BUTTON_MIDDLE = 0x02,

        BUTTON_EXTRA1 = 0x03,
        BUTTON_EXTRA2 = 0x04,
        BUTTON_EXTRA3 = 0x05,
        BUTTON_EXTRA4 = 0x06,
        BUTTON_EXTRA5 = 0x07,

        BUTTON_UNKOWN = 0xFF
    };

    struct KeyStruct {
        int scanCode;

        Snake::Key code;
        int modifiers;

        std::string string;
    };

    struct ButtonStruct {
        int scanCode;

        Snake::Button code;
        int modifiers;
    };

    Snake::KeyStruct getKeyFromScanCode(int scanCode, int scanMods, void* extra);
    Snake::ButtonStruct getButtonFromScanCode(int scanCode, int scanMods, void* extra);

    std::string getStringFromKeyCode(Snake::Key code, int modifiers);
};
#endif