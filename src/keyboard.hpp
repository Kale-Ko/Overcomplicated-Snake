#ifndef SNAKE_KEYBOARDH
#define SNAKE_KEYBOARDH

#include <string>

namespace Snake {
    typedef signed int KeyMod_t;
    namespace KeyMod {
        static KeyMod_t MOD_SHIFT = 0x01;
        static KeyMod_t MOD_CONTROL = 0x02;
        static KeyMod_t MOD_ALT = 0x04;
        static KeyMod_t MOD_META = 0x08;
        static KeyMod_t MOD_CAPS_LOCK = 0x10;
    };

    typedef signed int Key_t;
    namespace Key {
        static Key_t KEY_A = 0x00;
        static Key_t KEY_B = 0x01;
        static Key_t KEY_C = 0x02;
        static Key_t KEY_D = 0x03;
        static Key_t KEY_E = 0x04;
        static Key_t KEY_F = 0x05;
        static Key_t KEY_G = 0x06;
        static Key_t KEY_H = 0x07;
        static Key_t KEY_I = 0x08;
        static Key_t KEY_J = 0x09;
        static Key_t KEY_K = 0x0A;
        static Key_t KEY_L = 0x0B;
        static Key_t KEY_M = 0x0C;
        static Key_t KEY_N = 0x0D;
        static Key_t KEY_O = 0x0E;
        static Key_t KEY_P = 0x0F;
        static Key_t KEY_Q = 0x10;
        static Key_t KEY_R = 0x11;
        static Key_t KEY_S = 0x12;
        static Key_t KEY_T = 0x13;
        static Key_t KEY_U = 0x14;
        static Key_t KEY_V = 0x15;
        static Key_t KEY_W = 0x16;
        static Key_t KEY_X = 0x17;
        static Key_t KEY_Y = 0x18;
        static Key_t KEY_Z = 0x19;

        static Key_t KEY_0 = 0x20;
        static Key_t KEY_1 = 0x21;
        static Key_t KEY_2 = 0x22;
        static Key_t KEY_3 = 0x23;
        static Key_t KEY_4 = 0x24;
        static Key_t KEY_5 = 0x25;
        static Key_t KEY_6 = 0x26;
        static Key_t KEY_7 = 0x27;
        static Key_t KEY_8 = 0x28;
        static Key_t KEY_9 = 0x29;

        static Key_t KEY_COMMA = 0x30;
        static Key_t KEY_PERIOD = 0x31;
        static Key_t KEY_SLASH = 0x32;
        static Key_t KEY_SEMI_COLON = 0x33;
        static Key_t KEY_APOSTROPHE = 0x34;
        static Key_t KEY_OPEN_BRACKETS = 0x35;
        static Key_t KEY_CLOSE_BRACKETS = 0x36;
        static Key_t KEY_BACK_SLASH = 0x37;
        static Key_t KEY_MINUS = 0x38;
        static Key_t KEY_EQUALS = 0x39;
        static Key_t KEY_GRAVE = 0x3A;

        static Key_t KEY_SPACE = 0x40;
        static Key_t KEY_ENTER = 0x41;
        static Key_t KEY_BACKSPACE = 0x42;
        static Key_t KEY_TAB = 0x43;
        static Key_t KEY_ESCAPE = 0x44;

        static Key_t KEY_F1 = 0x50;
        static Key_t KEY_F2 = 0x51;
        static Key_t KEY_F3 = 0x52;
        static Key_t KEY_F4 = 0x53;
        static Key_t KEY_F5 = 0x54;
        static Key_t KEY_F6 = 0x55;
        static Key_t KEY_F7 = 0x56;
        static Key_t KEY_F8 = 0x57;
        static Key_t KEY_F9 = 0x58;
        static Key_t KEY_F10 = 0x59;
        static Key_t KEY_F11 = 0x5A;
        static Key_t KEY_F12 = 0x5B;

        static Key_t KEY_SHIFT = 0x60;
        static Key_t KEY_CONTROL = 0x61;
        static Key_t KEY_ALT = 0x62;
        static Key_t KEY_CAPS_LOCK = 0x63;
        static Key_t KEY_META = 0x64;

        static Key_t KEY_UNKOWN = 0xFF;
    };

    typedef signed int Button_t;
    namespace Button {
        static Button_t BUTTON_LEFT = 0x00;
        static Button_t BUTTON_RIGHT = 0x01;
        static Button_t BUTTON_MIDDLE = 0x02;

        static Button_t BUTTON_EXTRA1 = 0x03;
        static Button_t BUTTON_EXTRA2 = 0x04;
        static Button_t BUTTON_EXTRA3 = 0x05;
        static Button_t BUTTON_EXTRA4 = 0x06;
        static Button_t BUTTON_EXTRA5 = 0x07;

        static Button_t BUTTON_UNKOWN = 0xFF;
    };

    struct KeyStruct {
        int scanCode;

        Snake::Key_t code;
        Snake::KeyMod_t modifiers;

        std::string string;
    };

    struct ButtonStruct {
        int scanCode;

        Snake::Button_t code;
        Snake::KeyMod_t modifiers;
    };

    Snake::KeyStruct getKeyFromScanCode(int scanCode, int scanMods, void* extra);
    Snake::ButtonStruct getButtonFromScanCode(int scanCode, int scanMods, void* extra);

    std::string getStringFromKeyCode(Snake::Key_t code, Snake::KeyMod_t modifiers);
};
#endif