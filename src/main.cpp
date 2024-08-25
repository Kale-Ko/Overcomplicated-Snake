#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "game.hpp"
#include "window.hpp"
#include "renderer.hpp"

#ifdef SNAKE_DEBUG_INPUT
void mouseMoveListener(signed int x, signed int y)
{
    printf("MouseMove %i %i\n", x, y);
}

void mouseScrollListener(signed int x, signed int y)
{
    printf("MouseScroll %i %i\n", x, y);
}

void buttonDownListener(Snake::ButtonStruct button)
{
    printf("ButtonDown %i %i %x\n", button.scanCode, button.code, button.modifiers);
}

void buttonUpListener(Snake::ButtonStruct button)
{
    printf("ButtonUp %i %i %x\n", button.scanCode, button.code, button.modifiers);
}

void keyDownListener(Snake::KeyStruct key)
{
    printf("KeyDown %i %i %x %s\n", key.scanCode, key.code, key.modifiers, key.string.c_str());
}

void keyUpListener(Snake::KeyStruct key)
{
    printf("KeyUp %i %i %x %s\n", key.scanCode, key.code, key.modifiers, key.string.c_str());
}
#endif

int main(int argc, char* argv[])
{
    Snake::Window window((char*) "Overcomplicated Snake", NULL, Snake::WindowSize{ .width = 640, .height = 360 }, false, Snake::WindowPosition{ .x = 0, .y = 0 }, Snake::WindowPositionAlign::CENTER, false);
    if (window.init() < 0)
    {
        exit(0);
    }

#ifdef SNAKE_DEBUG_INPUT
    window.getEventManager()->registerMouseMoveListener(mouseMoveListener);
    window.getEventManager()->registerMouseScrollListener(mouseScrollListener);

    window.getEventManager()->registerButtonDownListener(buttonDownListener);
    window.getEventManager()->registerButtonUpListener(buttonUpListener);
    window.getEventManager()->registerKeyDownListener(keyDownListener);
    window.getEventManager()->registerKeyUpListener(keyUpListener);
#endif

    Snake::Game game(20, 20, 4, window.getEventManager());
    if (game.init() < 0)
    {
        exit(0);
    }

    Snake::Renderer renderer(&window, &game);
    if (renderer.init() < 0)
    {
        exit(0);
    }

    window.start();
    renderer.start();

    window.show();
    window.focus();

    game.start();

    while (true)
    {
    }

    renderer.destroy();
    game.destroy();
    window.destroy();
}