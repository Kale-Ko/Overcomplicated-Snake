#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "game.hpp"
#include "window.hpp"
#include "renderer.hpp"

#include <thread>

#if SNAKE_DEBUG_INPUT
void mouseMoveListener(const signed int x, const signed int y)
{
    printf("MouseMove %i %i\n", x, y);
}

void mouseScrollListener(const signed int x, const signed int y)
{
    printf("MouseScroll %i %i\n", x, y);
}

void buttonDownListener(const Snake::ButtonStruct button)
{
    printf("ButtonDown %i %x\n", button.code, button.modifiers);
}

void buttonUpListener(const Snake::ButtonStruct button)
{
    printf("ButtonUp %i %x\n", button.code, button.modifiers);
}

void keyDownListener(const Snake::KeyStruct key)
{
    printf("KeyDown %i %x %s\n", key.code, key.modifiers, key.string.c_str());
}

void keyUpListener(const Snake::KeyStruct key)
{
    printf("KeyUp %i %x %s\n", key.code, key.modifiers, key.string.c_str());
}
#endif

int main(int argc, char* argv[])
{
    Snake::Window window((char*) "Overcomplicated Snake", NULL, Snake::WindowSize{ .width = 640, .height = 360 }, false, Snake::WindowPosition{ .x = 0, .y = 0 }, Snake::WindowPositionAlign::CENTER, false);
    if (window.init() < 0)
    {
        exit(0);
    }

#if SNAKE_DEBUG_INPUT
    window.getEventManager()->registerMouseMoveListener(mouseMoveListener);
    window.getEventManager()->registerMouseScrollListener(mouseScrollListener);

    window.getEventManager()->registerButtonDownListener(buttonDownListener);
    window.getEventManager()->registerButtonUpListener(buttonUpListener);
    window.getEventManager()->registerKeyDownListener(keyDownListener);
    window.getEventManager()->registerKeyUpListener(keyUpListener);
#endif

    Snake::Game game(13, 13, 4, window.getEventManager());
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

    while (window.isRunning())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    renderer.destroy();
    game.destroy();
    window.destroy();

    return 0;
}