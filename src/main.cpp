#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "game.hpp"
#include "window.hpp"
#include "renderer.hpp"

int main(int argc, char* argv[]) {
    Snake::Game game;

    Snake::Window window((unsigned char*)"Overcomplicated Snake", NULL, Snake::WindowSize{ .width = 640,.height = 360 }, false, Snake::WindowPosition{ .x = 0,.y = 0 }, Snake::WindowPositionAlign::CENTER, false);
    window.init();

    Snake::Renderer renderer(&window, &game);
    renderer.init();

    window.start();
    renderer.start();

    window.show();
    window.focus();

    while (true) {

    }

    window.destroy();
}