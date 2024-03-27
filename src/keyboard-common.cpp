#include "keyboard.hpp"

#include <cstdlib>
#include <cmath>
#include <cstring>

#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace Snake {
    static std::map<Snake::Key, std::vector<std::string>> keyCodeToStrings = {
        { Snake::Key::KEY_A, { "a", "A", "A", "a" } },
        { Snake::Key::KEY_B, { "b", "B", "B", "b" } },
        { Snake::Key::KEY_C, { "c", "C", "C", "c" } },
        { Snake::Key::KEY_D, { "d", "D", "D", "d" } },
        { Snake::Key::KEY_E, { "e", "E", "E", "e" } },
        { Snake::Key::KEY_F, { "f", "F", "F", "f" } },
        { Snake::Key::KEY_G, { "g", "G", "G", "g" } },
        { Snake::Key::KEY_H, { "h", "H", "H", "h" } },
        { Snake::Key::KEY_I, { "i", "I", "I", "i" } },
        { Snake::Key::KEY_J, { "j", "J", "J", "j" } },
        { Snake::Key::KEY_K, { "k", "K", "K", "k" } },
        { Snake::Key::KEY_L, { "l", "L", "L", "l" } },
        { Snake::Key::KEY_M, { "m", "M", "M", "m" } },
        { Snake::Key::KEY_N, { "n", "N", "N", "n" } },
        { Snake::Key::KEY_O, { "o", "O", "O", "o" } },
        { Snake::Key::KEY_P, { "p", "P", "P", "p" } },
        { Snake::Key::KEY_Q, { "q", "Q", "Q", "q" } },
        { Snake::Key::KEY_R, { "r", "R", "R", "r" } },
        { Snake::Key::KEY_S, { "s", "S", "S", "s" } },
        { Snake::Key::KEY_T, { "t", "T", "T", "t" } },
        { Snake::Key::KEY_U, { "u", "U", "U", "u" } },
        { Snake::Key::KEY_V, { "v", "V", "V", "v" } },
        { Snake::Key::KEY_W, { "w", "W", "W", "w" } },
        { Snake::Key::KEY_X, { "x", "X", "X", "x" } },
        { Snake::Key::KEY_Y, { "y", "Y", "Y", "y" } },
        { Snake::Key::KEY_Z, { "z", "Z", "Z", "z" } },

        { Snake::Key::KEY_0, { "0", ")", "0", ")" } },
        { Snake::Key::KEY_1, { "1", "!", "1", "!" } },
        { Snake::Key::KEY_2, { "2", "@", "2", "@" } },
        { Snake::Key::KEY_3, { "3", "#", "3", "#" } },
        { Snake::Key::KEY_4, { "4", "$", "4", "$" } },
        { Snake::Key::KEY_5, { "5", "%", "5", "%" } },
        { Snake::Key::KEY_6, { "6", "^", "6", "^" } },
        { Snake::Key::KEY_7, { "7", "&", "7", "&" } },
        { Snake::Key::KEY_8, { "8", "*", "8", "*" } },
        { Snake::Key::KEY_9, { "9", "(", "9", "(" } },

        { Snake::Key::KEY_COMMA, { ",", "<", ",", "<" } },
        { Snake::Key::KEY_PERIOD, { ".", ">", ".", ">" } },
        { Snake::Key::KEY_SLASH, { "/", "?", "/", "?" } },
        { Snake::Key::KEY_SEMI_COLON, { ";", ":", ";", ":" } },
        { Snake::Key::KEY_APOSTROPHE, { "\'", "\"", "\'", "\"" } },
        { Snake::Key::KEY_OPEN_BRACKETS, { "[", "{", "[", "{" } },
        { Snake::Key::KEY_CLOSE_BRACKETS, { "]", "}", "]", "}" } },
        { Snake::Key::KEY_BACK_SLASH, { "\\", "|", "\\", "|" } },
        { Snake::Key::KEY_MINUS, { "-", "_", "-", "_" } },
        { Snake::Key::KEY_EQUALS, { "=", "+", "=", "+" } },
        { Snake::Key::KEY_GRAVE, { "`", "~", "`", "~" } },

        { Snake::Key::KEY_SPACE, { " ", " ", " ", " " } },
        { Snake::Key::KEY_ENTER, { "\r\n", "\r\n", "\r\n", "\r\n" } },
        { Snake::Key::KEY_BACKSPACE, { "\b", "\b", "\b", "\b" } },
        { Snake::Key::KEY_TAB, { "\t", "\t", "\t", "\t" } },

        { Snake::Key::KEY_UNKOWN, { "", "", "", "" } }
    };

    std::string getStringFromKeyCode(Snake::Key code, int modifiers) {
        if (keyCodeToStrings.contains(code)) {
            std::vector<std::string> vector = keyCodeToStrings.at(code);

            bool shift = (modifiers & Snake::KeyMod::MOD_SHIFT) == Snake::KeyMod::MOD_SHIFT;
            bool caps = (modifiers & Snake::KeyMod::MOD_CAPS_LOCK) == Snake::KeyMod::MOD_CAPS_LOCK;

            if (shift && !caps) {
                return vector.at(1);
            }
            else if (shift && caps) {
                return vector.at(3);
            }
            else if (!shift && caps) {
                return vector.at(2);
            }
            else {
                return vector.at(0);
            }
        }
        else {
            return keyCodeToStrings.at(Snake::Key::KEY_UNKOWN)[0];
        }
    }
};