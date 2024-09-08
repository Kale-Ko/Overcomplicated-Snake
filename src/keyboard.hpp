#ifndef SNAKE_KEYBOARDH
#define SNAKE_KEYBOARDH

#include <string>

namespace Snake
{
    typedef unsigned int KeyMod_t;

    namespace KeyMod
    {
        static const KeyMod_t MOD_SHIFT = 0x01;
        static const KeyMod_t MOD_CONTROL = 0x02;
        static const KeyMod_t MOD_ALT = 0x04;
        static const KeyMod_t MOD_META = 0x08;
        static const KeyMod_t MOD_CAPS_LOCK = 0x10;
        static const KeyMod_t MOD_NUM_LOCK = 0x20;
    };

    typedef unsigned int Key_t;

    namespace Key
    {
        static const Key_t KEY_A = 0x0000;
        static const Key_t KEY_B = 0x0001;
        static const Key_t KEY_C = 0x0002;
        static const Key_t KEY_D = 0x0003;
        static const Key_t KEY_E = 0x0004;
        static const Key_t KEY_F = 0x0005;
        static const Key_t KEY_G = 0x0006;
        static const Key_t KEY_H = 0x0007;
        static const Key_t KEY_I = 0x0008;
        static const Key_t KEY_J = 0x0009;
        static const Key_t KEY_K = 0x000A;
        static const Key_t KEY_L = 0x000B;
        static const Key_t KEY_M = 0x000C;
        static const Key_t KEY_N = 0x000D;
        static const Key_t KEY_O = 0x000E;
        static const Key_t KEY_P = 0x000F;
        static const Key_t KEY_Q = 0x0010;
        static const Key_t KEY_R = 0x0011;
        static const Key_t KEY_S = 0x0012;
        static const Key_t KEY_T = 0x0013;
        static const Key_t KEY_U = 0x0014;
        static const Key_t KEY_V = 0x0015;
        static const Key_t KEY_W = 0x0016;
        static const Key_t KEY_X = 0x0017;
        static const Key_t KEY_Y = 0x0018;
        static const Key_t KEY_Z = 0x0019;

        static const Key_t KEY_0 = 0x0100;
        static const Key_t KEY_1 = 0x0101;
        static const Key_t KEY_2 = 0x0102;
        static const Key_t KEY_3 = 0x0103;
        static const Key_t KEY_4 = 0x0104;
        static const Key_t KEY_5 = 0x0105;
        static const Key_t KEY_6 = 0x0106;
        static const Key_t KEY_7 = 0x0107;
        static const Key_t KEY_8 = 0x0108;
        static const Key_t KEY_9 = 0x0109;

        static const Key_t KEY_COMMA = 0x0200;
        static const Key_t KEY_PERIOD = 0x0201;
        static const Key_t KEY_SLASH = 0x0202;
        static const Key_t KEY_SEMI_COLON = 0x0203;
        static const Key_t KEY_APOSTROPHE = 0x0204;
        static const Key_t KEY_OPEN_BRACKETS = 0x0205;
        static const Key_t KEY_CLOSE_BRACKETS = 0x0206;
        static const Key_t KEY_BACK_SLASH = 0x0207;
        static const Key_t KEY_MINUS = 0x0208;
        static const Key_t KEY_EQUALS = 0x0209;
        static const Key_t KEY_GRAVE = 0x020A;

        static const Key_t KEY_SPACE = 0x0400;
        static const Key_t KEY_ENTER = 0x0401;
        static const Key_t KEY_BACKSPACE = 0x0402;
        static const Key_t KEY_TAB = 0x0403;
        static const Key_t KEY_ESCAPE = 0x0404;

        static const Key_t KEY_F1 = 0x0800;
        static const Key_t KEY_F2 = 0x0801;
        static const Key_t KEY_F3 = 0x0802;
        static const Key_t KEY_F4 = 0x0803;
        static const Key_t KEY_F5 = 0x0804;
        static const Key_t KEY_F6 = 0x0805;
        static const Key_t KEY_F7 = 0x0806;
        static const Key_t KEY_F8 = 0x0807;
        static const Key_t KEY_F9 = 0x0808;
        static const Key_t KEY_F10 = 0x0809;
        static const Key_t KEY_F11 = 0x080A;
        static const Key_t KEY_F12 = 0x080B;

        static const Key_t KEY_SHIFT = 0x1000;
        static const Key_t KEY_CONTROL = 0x1001;
        static const Key_t KEY_ALT = 0x1002;
        static const Key_t KEY_META = 0x1003;
        static const Key_t KEY_CAPS_LOCK = 0x1004;

        static const Key_t KEY_UNKOWN = 0xFFFF;
    };

    typedef unsigned int Button_t;

    namespace Button
    {
        static const Button_t BUTTON_LEFT = 0x0000;
        static const Button_t BUTTON_RIGHT = 0x0001;
        static const Button_t BUTTON_MIDDLE = 0x0002;

        static const Button_t BUTTON_EXTRA1 = 0x0003;
        static const Button_t BUTTON_EXTRA2 = 0x0004;
        static const Button_t BUTTON_EXTRA3 = 0x0005;
        static const Button_t BUTTON_EXTRA4 = 0x0006;
        static const Button_t BUTTON_EXTRA5 = 0x0007;

        static const Button_t BUTTON_UNKOWN = 0xFFFF;
    };

    struct KeyStruct
    {
        Snake::Key_t code;
        Snake::KeyMod_t modifiers;

        std::string string;
    };

    struct ButtonStruct
    {
        Snake::Button_t code;
        Snake::KeyMod_t modifiers;
    };

    const Snake::KeyStruct getKeyFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);
    const Snake::ButtonStruct getButtonFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra);

    std::string getStringFromKeyCode(const Snake::Key_t code, const Snake::KeyMod_t modifiers);
};
#endif