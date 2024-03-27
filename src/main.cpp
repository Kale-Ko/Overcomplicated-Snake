#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "window.hpp"

std::string string = "";

void keyDown(Snake::KeyStruct key) {
    // printf("keyDown %X '%s' (%X %X)\n", key.code, key.string.c_str(), key.scanCode, key.modifiers);

    string.append(key.string);
    printf("%s\n", string.c_str());
}
void keyUp(Snake::KeyStruct key) {
    // printf("keyUp %X '%s' (%X %X)\n", key.code, key.string.c_str(), key.scanCode, key.modifiers);
}

int main(int argc, char* argv[]) {
    printf("%i\n", argc);
    printf("%s\n", argv[0]);

    Snake::Window window((unsigned char*)"Overcomplicated Snake", NULL, Snake::WindowSize{ .width = 640,.height = 360 }, false, Snake::WindowPosition{ .x = 0,.y = 0 }, Snake::WindowPositionAlign::CENTER, false);
    window.init();

    window.getEventManager()->registerKeyDownListener(&keyDown);
    window.getEventManager()->registerKeyUpListener(&keyUp);

    window.start();

    window.show();
    window.focus();

    while (true) {

    }

    window.destroy();
}