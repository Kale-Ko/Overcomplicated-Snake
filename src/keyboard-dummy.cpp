#include "keyboard-common.cpp"

namespace Snake
{
    const Snake::KeyStruct getKeyFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra)
    {
        return getKeyStructFromString(*((std::string*) extra));
    }

    const Snake::ButtonStruct getButtonFromScanCode(const unsigned int scanCode, const unsigned int modifiers, const void* const extra)
    {
        throw "Unimplemented";
    }
};