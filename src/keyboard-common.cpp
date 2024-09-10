#include "keyboard.hpp"

#include <cstdlib>
#include <cstring>

#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace Snake
{
    static const std::map<const Snake::Key_t, const std::vector<const char*>> keyCodeToStrings = {
        { Snake::Key::KEY_A,              { "a", "A", "A", "a" }             },
        { Snake::Key::KEY_B,              { "b", "B", "B", "b" }             },
        { Snake::Key::KEY_C,              { "c", "C", "C", "c" }             },
        { Snake::Key::KEY_D,              { "d", "D", "D", "d" }             },
        { Snake::Key::KEY_E,              { "e", "E", "E", "e" }             },
        { Snake::Key::KEY_F,              { "f", "F", "F", "f" }             },
        { Snake::Key::KEY_G,              { "g", "G", "G", "g" }             },
        { Snake::Key::KEY_H,              { "h", "H", "H", "h" }             },
        { Snake::Key::KEY_I,              { "i", "I", "I", "i" }             },
        { Snake::Key::KEY_J,              { "j", "J", "J", "j" }             },
        { Snake::Key::KEY_K,              { "k", "K", "K", "k" }             },
        { Snake::Key::KEY_L,              { "l", "L", "L", "l" }             },
        { Snake::Key::KEY_M,              { "m", "M", "M", "m" }             },
        { Snake::Key::KEY_N,              { "n", "N", "N", "n" }             },
        { Snake::Key::KEY_O,              { "o", "O", "O", "o" }             },
        { Snake::Key::KEY_P,              { "p", "P", "P", "p" }             },
        { Snake::Key::KEY_Q,              { "q", "Q", "Q", "q" }             },
        { Snake::Key::KEY_R,              { "r", "R", "R", "r" }             },
        { Snake::Key::KEY_S,              { "s", "S", "S", "s" }             },
        { Snake::Key::KEY_T,              { "t", "T", "T", "t" }             },
        { Snake::Key::KEY_U,              { "u", "U", "U", "u" }             },
        { Snake::Key::KEY_V,              { "v", "V", "V", "v" }             },
        { Snake::Key::KEY_W,              { "w", "W", "W", "w" }             },
        { Snake::Key::KEY_X,              { "x", "X", "X", "x" }             },
        { Snake::Key::KEY_Y,              { "y", "Y", "Y", "y" }             },
        { Snake::Key::KEY_Z,              { "z", "Z", "Z", "z" }             },

        { Snake::Key::KEY_0,              { "0", ")", "0", ")" }             },
        { Snake::Key::KEY_1,              { "1", "!", "1", "!" }             },
        { Snake::Key::KEY_2,              { "2", "@", "2", "@" }             },
        { Snake::Key::KEY_3,              { "3", "#", "3", "#" }             },
        { Snake::Key::KEY_4,              { "4", "$", "4", "$" }             },
        { Snake::Key::KEY_5,              { "5", "%", "5", "%" }             },
        { Snake::Key::KEY_6,              { "6", "^", "6", "^" }             },
        { Snake::Key::KEY_7,              { "7", "&", "7", "&" }             },
        { Snake::Key::KEY_8,              { "8", "*", "8", "*" }             },
        { Snake::Key::KEY_9,              { "9", "(", "9", "(" }             },

        { Snake::Key::KEY_COMMA,          { ",", "<", ",", "<" }             },
        { Snake::Key::KEY_PERIOD,         { ".", ">", ".", ">" }             },
        { Snake::Key::KEY_SLASH,          { "/", "?", "/", "?" }             },
        { Snake::Key::KEY_SEMI_COLON,     { ";", ":", ";", ":" }             },
        { Snake::Key::KEY_APOSTROPHE,     { "\'", "\"", "\'", "\"" }         },
        { Snake::Key::KEY_OPEN_BRACKETS,  { "[", "{", "[", "{" }             },
        { Snake::Key::KEY_CLOSE_BRACKETS, { "]", "}", "]", "}" }             },
        { Snake::Key::KEY_BACK_SLASH,     { "\\", "|", "\\", "|" }           },
        { Snake::Key::KEY_MINUS,          { "-", "_", "-", "_" }             },
        { Snake::Key::KEY_EQUALS,         { "=", "+", "=", "+" }             },
        { Snake::Key::KEY_GRAVE,          { "`", "~", "`", "~" }             },

        { Snake::Key::KEY_SPACE,          { " ", " ", " ", " " }             },
        { Snake::Key::KEY_ENTER,          { "\r\n", "\r\n", "\r\n", "\r\n" } },
        { Snake::Key::KEY_BACKSPACE,      { "\b", "\b", "\b", "\b" }         },
        { Snake::Key::KEY_TAB,            { "\t", "\t", "\t", "\t" }         },

#if FN_KEYS_ARE_EMPTY_STRINGS
        { Snake::Key::KEY_ESCAPE,         { "", "", "", "" }                 },

        { Snake::Key::KEY_F1,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F2,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F3,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F4,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F5,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F6,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F7,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F8,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F9,             { "", "", "", "" }                 },
        { Snake::Key::KEY_F10,            { "", "", "", "" }                 },
        { Snake::Key::KEY_F11,            { "", "", "", "" }                 },
        { Snake::Key::KEY_F12,            { "", "", "", "" }                 },

        { Snake::Key::KEY_SHIFT,          { "", "", "", "" }                 },
        { Snake::Key::KEY_CONTROL,        { "", "", "", "" }                 },
        { Snake::Key::KEY_ALT,            { "", "", "", "" }                 },
        { Snake::Key::KEY_META,           { "", "", "", "" }                 },
        { Snake::Key::KEY_CAPS_LOCK,      { "", "", "", "" }                 },
#endif

        { Snake::Key::KEY_UNKOWN,         { "�", "�", "�", "�" }     }
    };

    std::string getStringFromKeyCode(const Snake::Key_t code, const Snake::KeyMod_t modifiers)
    {
        if (keyCodeToStrings.contains(code))
        {
            const std::vector<const char*> vector = keyCodeToStrings.at(code);

            bool shift = (modifiers & Snake::KeyMod::MOD_SHIFT) == Snake::KeyMod::MOD_SHIFT;
            bool caps = (modifiers & Snake::KeyMod::MOD_CAPS_LOCK) == Snake::KeyMod::MOD_CAPS_LOCK;

            int index = (shift ? (caps ? 3 : 1) : (caps ? 2 : 0));

            const char* data = vector.at(index);
            return std::string(data);
        } else
        {
            const char* data = keyCodeToStrings.at(Snake::Key::KEY_UNKOWN).at(0);
            return std::string(data);
        }
    }

    // Get ready for the most inefficient code you have ever read
    Snake::KeyStruct getKeyStructFromString(const std::string string)
    {
        for (auto entry : keyCodeToStrings)
        {
            for (int i = 0; i < entry.second.size(); i++)
            {
                if (string.compare(entry.second.at(i)) == 0)
                {
                    Snake::Key_t code = entry.first;

                    Snake::KeyMod_t modifiers = 0;
                    switch (i)
                    {
                        case 1:
                            modifiers = Snake::KeyMod::MOD_SHIFT;
                            break;
                        case 2:
                            modifiers = Snake::KeyMod::MOD_CAPS_LOCK;
                            break;
                        case 3:
                            modifiers = Snake::KeyMod::MOD_SHIFT | Snake::KeyMod::MOD_CAPS_LOCK;
                            break;
                    }

                    return Snake::KeyStruct{ .code = code, .modifiers = modifiers, .string = entry.second[i] };
                }
            }
        }

        return Snake::KeyStruct{ .code = Snake::Key::KEY_UNKOWN, .modifiers = 0, .string = "" };
    }
};