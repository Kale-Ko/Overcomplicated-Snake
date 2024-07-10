#ifndef SNAKE_KEYBOARDH
#define SNAKE_KEYBOARDH

#include <string>

namespace Snake {
    typedef unsigned int KeyMod_t;
    namespace KeyMod {
        const static KeyMod_t MOD_SHIFT = 0x01;
        const static KeyMod_t MOD_CONTROL = 0x02;
        const static KeyMod_t MOD_ALT = 0x04;
        const static KeyMod_t MOD_META = 0x08;
        const static KeyMod_t MOD_CAPS_LOCK = 0x10;
    };

    typedef unsigned int Key_t;
    namespace Key {
        const static Key_t KEY_A = 0x00;
        const static Key_t KEY_B = 0x01;
        const static Key_t KEY_C = 0x02;
        const static Key_t KEY_D = 0x03;
        const static Key_t KEY_E = 0x04;
        const static Key_t KEY_F = 0x05;
        const static Key_t KEY_G = 0x06;
        const static Key_t KEY_H = 0x07;
        const static Key_t KEY_I = 0x08;
        const static Key_t KEY_J = 0x09;
        const static Key_t KEY_K = 0x0A;
        const static Key_t KEY_L = 0x0B;
        const static Key_t KEY_M = 0x0C;
        const static Key_t KEY_N = 0x0D;
        const static Key_t KEY_O = 0x0E;
        const static Key_t KEY_P = 0x0F;
        const static Key_t KEY_Q = 0x10;
        const static Key_t KEY_R = 0x11;
        const static Key_t KEY_S = 0x12;
        const static Key_t KEY_T = 0x13;
        const static Key_t KEY_U = 0x14;
        const static Key_t KEY_V = 0x15;
        const static Key_t KEY_W = 0x16;
        const static Key_t KEY_X = 0x17;
        const static Key_t KEY_Y = 0x18;
        const static Key_t KEY_Z = 0x19;

        const static Key_t KEY_0 = 0x20;
        const static Key_t KEY_1 = 0x21;
        const static Key_t KEY_2 = 0x22;
        const static Key_t KEY_3 = 0x23;
        const static Key_t KEY_4 = 0x24;
        const static Key_t KEY_5 = 0x25;
        const static Key_t KEY_6 = 0x26;
        const static Key_t KEY_7 = 0x27;
        const static Key_t KEY_8 = 0x28;
        const static Key_t KEY_9 = 0x29;

        const static Key_t KEY_COMMA = 0x30;
        const static Key_t KEY_PERIOD = 0x31;
        const static Key_t KEY_SLASH = 0x32;
        const static Key_t KEY_SEMI_COLON = 0x33;
        const static Key_t KEY_APOSTROPHE = 0x34;
        const static Key_t KEY_OPEN_BRACKETS = 0x35;
        const static Key_t KEY_CLOSE_BRACKETS = 0x36;
        const static Key_t KEY_BACK_SLASH = 0x37;
        const static Key_t KEY_MINUS = 0x38;
        const static Key_t KEY_EQUALS = 0x39;
        const static Key_t KEY_GRAVE = 0x3A;

        const static Key_t KEY_SPACE = 0x40;
        const static Key_t KEY_ENTER = 0x41;
        const static Key_t KEY_BACKSPACE = 0x42;
        const static Key_t KEY_TAB = 0x43;
        const static Key_t KEY_ESCAPE = 0x44;

        const static Key_t KEY_F1 = 0x50;
        const static Key_t KEY_F2 = 0x51;
        const static Key_t KEY_F3 = 0x52;
        const static Key_t KEY_F4 = 0x53;
        const static Key_t KEY_F5 = 0x54;
        const static Key_t KEY_F6 = 0x55;
        const static Key_t KEY_F7 = 0x56;
        const static Key_t KEY_F8 = 0x57;
        const static Key_t KEY_F9 = 0x58;
        const static Key_t KEY_F10 = 0x59;
        const static Key_t KEY_F11 = 0x5A;
        const static Key_t KEY_F12 = 0x5B;

        const static Key_t KEY_SHIFT = 0x60;
        const static Key_t KEY_CONTROL = 0x61;
        const static Key_t KEY_ALT = 0x62;
        const static Key_t KEY_CAPS_LOCK = 0x63;
        const static Key_t KEY_META = 0x64;

        const static Key_t KEY_UNKOWN = 0xFF;
    };

    typedef unsigned int Button_t;
    namespace Button {
        const static Button_t BUTTON_LEFT = 0x00;
        const static Button_t BUTTON_RIGHT = 0x01;
        const static Button_t BUTTON_MIDDLE = 0x02;

        const static Button_t BUTTON_EXTRA1 = 0x03;
        const static Button_t BUTTON_EXTRA2 = 0x04;
        const static Button_t BUTTON_EXTRA3 = 0x05;
        const static Button_t BUTTON_EXTRA4 = 0x06;
        const static Button_t BUTTON_EXTRA5 = 0x07;

        const static Button_t BUTTON_UNKOWN = 0xFF;
    };

    struct KeyStruct {
        unsigned int scanCode;

        Snake::Key_t code;
        Snake::KeyMod_t modifiers;

        std::string string;
    };

    struct ButtonStruct {
        unsigned int scanCode;

        Snake::Button_t code;
        Snake::KeyMod_t modifiers;
    };

    const Snake::KeyStruct getKeyFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
    const Snake::ButtonStruct getButtonFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);

    std::string getStringFromKeyCode(const Snake::Key_t code, const Snake::KeyMod_t modifiers);
};
#endif