#include "window.hpp"

#include "windowevents.hpp"

#include <cstdlib>
#include <cstring>
#include <cmath>

#include <thread>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>

typedef Display X11Display;
typedef Screen X11Screen;
typedef Window X11Window;

namespace Snake
{
    struct X11WindowStruct
    {
        X11Display* display;
        X11Screen* screen;
        X11Window window;

        WindowPosition screenOffset;
        WindowSize screenSize;
    };

    static int* x11RefCount = new int{ 0 };

    Snake::Window::Window(const char* const title, const Snake::WindowIcon* const icon, const Snake::WindowSize size, const bool resizable, const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const bool mouseLockEnabled)
    {
        this->title = title;
        this->icon = icon;

        this->size = size;
        this->resizable = resizable;

        this->position = position;
        this->positionAlign = positionAlign;
        this->monitorType = WindowMonitorType::PRIMARY;

        this->mouseLockEnabled = mouseLockEnabled;
    }

    Snake::Window::Window(const char* const title, const Snake::WindowIcon* const icon, const Snake::WindowSize size, const bool resizable, const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const Snake::WindowMonitorType monitorType, const bool mouseLockEnabled)
    {
        this->title = title;
        this->icon = icon;

        this->size = size;
        this->resizable = resizable;

        this->position = position;
        this->positionAlign = positionAlign;
        this->monitorType = monitorType;

        this->mouseLockEnabled = mouseLockEnabled;
    }

    Snake::Window::~Window()
    {
        if (this->initialized && !this->destroyed)
        {
            this->destroy();
        }
    }

    const char* Snake::Window::getTitle()
    {
        return this->title;
    }

    void Snake::Window::setTitle(const char* const title)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->title = title;

        if (this->initialized)
        {
            Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

            XTextProperty titleText;
            XStringListToTextProperty((char**) (&this->title), 1, &titleText);
            XSetWMName(windowStruct->display, windowStruct->window, &titleText);
        }
    }

    const Snake::WindowIcon* Snake::Window::getIcon()
    {
        return this->icon;
    }

    void Snake::Window::setIcon(const Snake::WindowIcon* const icon)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->icon = icon;

        if (this->initialized)
        {
            Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

            if (icon != NULL)
            {
                Pixmap pixmap = XCreatePixmapFromBitmapData(windowStruct->display, windowStruct->window, (char*) this->icon->data, this->icon->width, this->icon->height, windowStruct->screen->white_pixel, windowStruct->screen->black_pixel, 32);

                XWMHints hints;
                hints.flags = IconPixmapHint;
                hints.icon_pixmap = pixmap;
                XSetWMHints(windowStruct->display, windowStruct->window, &hints);
            } else
            {
                XWMHints hints;
                hints.flags = IconPixmapHint;
                hints.icon_pixmap = None;
                XSetWMHints(windowStruct->display, windowStruct->window, &hints);
            }
        }
    }

    const Snake::WindowSize Snake::Window::getSize()
    {
        return this->size;
    }

    const bool Snake::Window::isResizable()
    {
        return this->resizable;
    }

    void Snake::Window::setSize(const Snake::WindowSize size)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->resizable)
        {
            fprintf(stderr, "Window is not resizable.\n");
            return;
        }

        this->size = size;

        if (this->initialized)
        {
            Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

            if (this->position.x < 0 || this->position.x + size.width >= windowStruct->screenSize.width || this->position.y < 0 || this->position.y + size.height >= windowStruct->screenSize.height)
            {
                fprintf(stderr, "Size is outside screen bounds.\n");
                return;
            }

            XResizeWindow(windowStruct->display, windowStruct->window, this->size.width, this->size.height);
        }
    }

    void Snake::Window::__setSize(const Snake::WindowSize size)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->size = size;
    }

    const Snake::WindowPosition Snake::Window::getPosition()
    {
        return this->position;
    }

    const Snake::WindowPositionAlign Snake::Window::getPositionAlign()
    {
        return this->positionAlign;
    }

    const Snake::WindowMonitorType Snake::Window::getMonitorType()
    {
        return this->monitorType;
    }

    void Snake::Window::setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->position = position;
        this->positionAlign = positionAlign;

        if (this->initialized)
        {
            Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

            if (position.x < 0 || position.x + this->size.width >= windowStruct->screenSize.width || position.y < 0 || position.y + this->size.height >= windowStruct->screenSize.height)
            {
                fprintf(stderr, "Position is outside screen bounds.\n");
                return;
            }

            switch (this->positionAlign)
            {
                case TOP_LEFT:
                    XMoveWindow(windowStruct->display, windowStruct->window, windowStruct->screenOffset.x + this->position.x, windowStruct->screenOffset.y + this->position.y);
                    break;
                case CENTER:
                    XMoveWindow(windowStruct->display, windowStruct->window, windowStruct->screenOffset.x + this->position.x + ((windowStruct->screenSize.width / 2) - (this->size.width / 2)), windowStruct->screenOffset.y + this->position.y + ((windowStruct->screenSize.height / 2) - (this->size.height / 2)));
                    break;
            }
        }
    }

    void Snake::Window::setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign, const Snake::WindowMonitorType monitorType)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->position = position;
        this->positionAlign = positionAlign;
        this->monitorType = monitorType;

        if (this->initialized)
        {
            Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

            if (position.x < 0 || position.x + this->size.width >= windowStruct->screenSize.width || position.y < 0 || position.y + this->size.height >= windowStruct->screenSize.height)
            {
                fprintf(stderr, "Position is outside screen bounds.\n");
                return;
            }

            switch (this->positionAlign)
            {
                case TOP_LEFT:
                    XMoveWindow(windowStruct->display, windowStruct->window, windowStruct->screenOffset.x + this->position.x, windowStruct->screenOffset.y + this->position.y);
                    break;
                case CENTER:
                    XMoveWindow(windowStruct->display, windowStruct->window, windowStruct->screenOffset.x + this->position.x + ((windowStruct->screenSize.width / 2) - (this->size.width / 2)), windowStruct->screenOffset.y + this->position.y + ((windowStruct->screenSize.height / 2) - (this->size.height / 2)));
                    break;
            }
        }
    }

    void Snake::Window::__setPosition(const Snake::WindowPosition position, const Snake::WindowPositionAlign positionAlign)
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }

        this->position = position;
        this->positionAlign = positionAlign;
    }

    Snake::EventManager* const Snake::Window::getEventManager()
    {
        return &this->eventManager;
    }

    bool Snake::Window::isValid()
    {
        return this->initialized && !this->destroyed;
    }

    int Snake::Window::init()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return -2;
        }
        if (this->initialized)
        {
            fprintf(stderr, "Window is already initialized.\n");
            return -2;
        }

        if (*x11RefCount == 0)
        {
            (*x11RefCount)++;

            if (XInitThreads() == 0)
            {
                fprintf(stderr, "Failed to initialize X11.\n");
                return -1;
            }
        }

        this->windowStruct = new Snake::X11WindowStruct();
        Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;
        this->initialized = true;

        windowStruct->display = XOpenDisplay(NULL);
        if (windowStruct->display == NULL)
        {
            fprintf(stderr, "Failed open X11 display.\n");
            return -1;
        }

        windowStruct->screen = XDefaultScreenOfDisplay(windowStruct->display);
        if (windowStruct->screen == NULL)
        {
            fprintf(stderr, "Failed to open X11 screen.\n");
            return -1;
        }

        windowStruct->screenOffset = WindowPosition{ 0, 0 };
        windowStruct->screenSize = WindowSize{ (unsigned int) windowStruct->screen->width, (unsigned int) windowStruct->screen->height };

        {
            X11Window _window, _window2;
            int mouseX = -1, mouseY = -1;
            int _windowX, _windowY;
            unsigned int _mods;
            if (XQueryPointer(windowStruct->display, windowStruct->screen->root, &_window, &_window2, &mouseX, &mouseY, &_windowX, &_windowY, &_mods) <= 0)
            {
                fprintf(stderr, "Failed to query mouse pointer.\n");
                return -1;
            }

            int _opCode, _event, _error;
            if (XQueryExtension(windowStruct->display, "RANDR", &_opCode, &_event, &_error) > 0)
            {
                RROutput primaryOutput = XRRGetOutputPrimary(windowStruct->display, windowStruct->screen->root);

                XRRScreenResources* xScreenResources = XRRGetScreenResources(windowStruct->display, windowStruct->screen->root);

                for (int j = 0; j < xScreenResources->noutput; j++)
                {
                    XRROutputInfo* xOutputInfo = XRRGetOutputInfo(windowStruct->display, xScreenResources, xScreenResources->outputs[j]);

                    if (xOutputInfo->connection == RR_Connected && xOutputInfo->crtc > 0)
                    {
                        XRRCrtcInfo* xCrtcInfo = XRRGetCrtcInfo(windowStruct->display, xScreenResources, xOutputInfo->crtc);

                        bool found = false;
                        switch (this->monitorType)
                        {
                            case PRIMARY:
                                if (xScreenResources->outputs[j] == primaryOutput)
                                {
                                    windowStruct->screenOffset = WindowPosition{ xCrtcInfo->x, xCrtcInfo->y };
                                    windowStruct->screenSize = WindowSize{ xCrtcInfo->width, xCrtcInfo->height };
                                    found = true;
                                }
                                break;
                            case CURRENT:
                                if (mouseX >= xCrtcInfo->x && mouseY >= xCrtcInfo->y && mouseX < (xCrtcInfo->x + xCrtcInfo->width) && mouseY < (xCrtcInfo->y + xCrtcInfo->height))
                                {
                                    windowStruct->screenOffset = WindowPosition{ xCrtcInfo->x, xCrtcInfo->y };
                                    windowStruct->screenSize = WindowSize{ xCrtcInfo->width, xCrtcInfo->height };
                                    found = true;
                                }
                                break;
                        }
                        if (found)
                        {
                            break;
                        }

                        XRRFreeCrtcInfo(xCrtcInfo);
                    }

                    XRRFreeOutputInfo(xOutputInfo);
                }

                XRRFreeScreenResources(xScreenResources);
            }

            {
                Atom workAreaAtom = XInternAtom(windowStruct->display, "_NET_WORKAREA", False);
                if (workAreaAtom != None)
                {
                    Atom workType;
                    int workFormat;
                    unsigned long workItemCount, workBytesAfter;
                    unsigned char* workAreaData;

                    int workStatus = XGetWindowProperty(windowStruct->display, windowStruct->screen->root, workAreaAtom, 0, LONG_MAX, False, XA_CARDINAL, &workType, &workFormat, &workItemCount, &workBytesAfter, &workAreaData);
                    if (workStatus >= 0)
                    {
                        long desktopIndex = 0;

                        Atom desktopAtom = XInternAtom(windowStruct->display, "_NET_CURRENT_DESKTOP", False);
                        if (desktopAtom != None)
                        {
                            Atom desktopType;
                            int desktopFormat;
                            unsigned long desktopItemCount, desktopBytesAfter;
                            unsigned char* desktopData;

                            int desktopStatus = XGetWindowProperty(windowStruct->display, windowStruct->screen->root, desktopAtom, 0, LONG_MAX, False, XA_CARDINAL, &desktopType, &desktopFormat, &desktopItemCount, &desktopBytesAfter, &desktopData);
                            if (desktopStatus >= 0)
                            {
                                long* desktop = (long*) desktopData;
                                if (desktopItemCount > 0)
                                {
                                    desktopIndex = desktop[0] * 4;
                                }

                                XFree(desktopData);
                            }
                        }

                        if (workItemCount >= 4 && desktopIndex + 3 < workItemCount)
                        {
                            long* workArea = (long*) workAreaData;
                            int workX = workArea[desktopIndex + 0];
                            int workY = workArea[desktopIndex + 1];
                            unsigned int workWidth = workArea[desktopIndex + 2];
                            unsigned int workHeight = workArea[desktopIndex + 3];

                            if (windowStruct->screenOffset.x < workX)
                            {
                                windowStruct->screenSize.width -= workX - windowStruct->screenOffset.x;
                                windowStruct->screenOffset.x = workX;
                            }

                            if (windowStruct->screenOffset.y < workY)
                            {
                                windowStruct->screenSize.height -= workY - windowStruct->screenOffset.y;
                                windowStruct->screenOffset.y = workY;
                            }

                            if (windowStruct->screenOffset.x + windowStruct->screenSize.width > workX + workWidth)
                            {
                                windowStruct->screenSize.width = workX - windowStruct->screenOffset.x + workWidth;
                            }
                            if (windowStruct->screenOffset.y + windowStruct->screenSize.height > workY + workHeight)
                            {
                                windowStruct->screenSize.height = workY - windowStruct->screenOffset.y + workHeight;
                            }
                        }

                        XFree(workAreaData);
                    }
                }
            }
        }

        switch (this->positionAlign)
        {
            case TOP_LEFT:
                windowStruct->window = XCreateSimpleWindow(windowStruct->display, windowStruct->screen->root, windowStruct->screenOffset.x + this->position.x, windowStruct->screenOffset.y + this->position.y, this->size.width, this->size.height, 1, windowStruct->screen->black_pixel, windowStruct->screen->black_pixel);
                break;
            case CENTER:
                windowStruct->window = XCreateSimpleWindow(windowStruct->display, windowStruct->screen->root, windowStruct->screenOffset.x + this->position.x + ((windowStruct->screenSize.width / 2) - (this->size.width / 2)), windowStruct->screenOffset.y + this->position.y + ((windowStruct->screenSize.height / 2) - (this->size.height / 2)), this->size.width, this->size.height, 1, windowStruct->screen->black_pixel, windowStruct->screen->black_pixel);
                break;
        }

        if (windowStruct->window == 0)
        {
            fprintf(stderr, "Failed to create X11 window.\n");
            return -1;
        }

        XSetWindowAttributes windowAttributes;
        windowAttributes.backing_store = WhenMapped;
        windowAttributes.save_under = True;
        XChangeWindowAttributes(windowStruct->display, windowStruct->window, CWBackingStore | CWSaveUnder, &windowAttributes);

        XTextProperty titleText;
        XStringListToTextProperty((char**) (&this->title), 1, &titleText);
        XSetWMName(windowStruct->display, windowStruct->window, &titleText);

        if (icon != NULL)
        {
            Pixmap pixmap = XCreatePixmapFromBitmapData(windowStruct->display, windowStruct->window, (char*) this->icon->data, this->icon->width, this->icon->height, windowStruct->screen->white_pixel, windowStruct->screen->black_pixel, 32);

            XWMHints hints;
            hints.flags = IconPixmapHint;
            hints.icon_pixmap = pixmap;
            XSetWMHints(windowStruct->display, windowStruct->window, &hints);
        } else
        {
            XWMHints hints;
            hints.flags = IconPixmapHint;
            hints.icon_pixmap = None;
            XSetWMHints(windowStruct->display, windowStruct->window, &hints);
        }

        XClassHint classInfo;
        classInfo.res_name = (char*) this->title;
        classInfo.res_class = (char*) "WindowMain";
        XSetClassHint(windowStruct->display, windowStruct->window, &classInfo);

        if (!this->resizable)
        {
            XSizeHints sizeInfo;
            sizeInfo.flags = PMinSize | PMaxSize;
            sizeInfo.min_width = this->size.width;
            sizeInfo.min_height = this->size.height;
            sizeInfo.max_width = this->size.width;
            sizeInfo.max_height = this->size.height;
            XSetWMNormalHints(windowStruct->display, windowStruct->window, &sizeInfo);
        }

        return 1;
    }

    int Snake::Window::destroy()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is already destroyed.\n");
            return -2;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Window is not initialized.\n");
            return -2;
        }

        if (this->running)
        {
            this->stop();
        }

        this->destroyed = true;
        this->initialized = false;

        Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

        XDestroyWindow(windowStruct->display, windowStruct->window);

        XCloseDisplay(windowStruct->display);

        (*x11RefCount)--;
        if (*x11RefCount == 0)
        {
            XFreeThreads();
        }

        delete(Snake::X11WindowStruct*) this->windowStruct;

        return 1;
    }

    void Snake::Window::show()
    {
        Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

        XMapWindow(windowStruct->display, windowStruct->window);
    }

    void Snake::Window::hide()
    {
        Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

        XUnmapWindow(windowStruct->display, windowStruct->window);
    }

    void Snake::Window::focus()
    {
        Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

        XRaiseWindow(windowStruct->display, windowStruct->window);
    }

    void run(Snake::Window* const context, Snake::X11WindowStruct* const windowStruct)
    {
        XSelectInput(windowStruct->display, windowStruct->window, FocusChangeMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask);

        Atom wmDeleteMessage = XInternAtom(windowStruct->display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(windowStruct->display, windowStruct->window, &wmDeleteMessage, 1);

        XFlush(windowStruct->display);

        XEvent event;
        while (context->isRunning())
        {
            XNextEvent(windowStruct->display, &event);

            switch (event.type)
            {
                case FocusIn:
                    if (event.xfocus.type != FocusIn)
                    {
                        continue;
                    }

                    if (context->isMouseLockEnabled() && !context->isMouseLocked())
                    {
                        context->lockMouse();
                    }

                    context->getEventManager()->emitWindowFocusEvent();

                    break;
                case FocusOut:
                    if (event.xfocus.type != FocusOut)
                    {
                        continue;
                    }

                    if (context->isMouseLocked())
                    {
                        context->unlockMouse();
                    }

                    context->getEventManager()->emitWindowUnfocusEvent();

                    break;
                case ClientMessage:
                    if ((Atom) event.xclient.data.l[0] == wmDeleteMessage)
                    {
                        context->getEventManager()->emitWindowCloseEvent();

                        context->stop();
                    }

                    break;
                case ConfigureNotify:
                    if (event.xconfigure.type != ConfigureNotify)
                    {
                        continue;
                    }

                    Snake::WindowPosition previousPosition;
                    previousPosition = context->getPosition();
                    Snake::WindowSize previousSize;
                    previousSize = context->getSize();

                    context->__setPosition(Snake::WindowPosition{ .x = event.xconfigure.x, .y = event.xconfigure.y }, Snake::WindowPositionAlign::TOP_LEFT); // TODO Don't change position align
                    context->__setSize(Snake::WindowSize{ .width = (unsigned int) event.xconfigure.width, .height = (unsigned int) event.xconfigure.height });

                    if (event.xconfigure.x != previousPosition.x || event.xconfigure.y != previousPosition.y)
                    {
                        context->getEventManager()->emitWindowMoveEvent(event.xconfigure.x, event.xconfigure.y);
                    }

                    if ((unsigned int) event.xconfigure.width != previousSize.width || (unsigned int) event.xconfigure.height != previousSize.height)
                    {
                        context->getEventManager()->emitWindowResizeEvent(event.xconfigure.width, event.xconfigure.height);
                    }

                    break;
                case MotionNotify:
                    if (event.xmotion.type != MotionNotify)
                    {
                        continue;
                    }

                    if (context->isMouseLockEnabled() && context->isMouseLocked())
                    {
                        if (event.xmotion.x == (int) context->getSize().width / 2 && event.xmotion.y == (int) context->getSize().height / 2)
                        {
                            continue;
                        }

                        context->getEventManager()->emitMouseMoveEvent(event.xmotion.x - (context->getSize().width / 2), event.xmotion.y - (context->getSize().height / 2));

                        XWarpPointer(windowStruct->display, None, windowStruct->window, 0, 0, 0, 0, context->getSize().width / 2, context->getSize().height / 2);
                    } else
                    {
                        context->getEventManager()->emitMouseMoveEvent(event.xmotion.x, event.xmotion.y);
                    }

                    break;
                case ButtonPress:
                    if (event.xbutton.type != ButtonPress)
                    {
                        continue;
                    }

                    if (event.xbutton.button == 0x04)
                    {
                        context->getEventManager()->emitMouseScrollEvent(0.0, 1.0);

                        continue;
                    } else if (event.xbutton.button == 0x05)
                    {
                        context->getEventManager()->emitMouseScrollEvent(0.0, -1.0);

                        continue;
                    } else if (event.xbutton.button == 0x06)
                    {
                        context->getEventManager()->emitMouseScrollEvent(1.0, 0.0);

                        continue;
                    } else if (event.xbutton.button == 0x07)
                    {
                        context->getEventManager()->emitMouseScrollEvent(-1.0, 0.0);

                        continue;
                    }

                    if (context->isMouseLockEnabled() && !context->isMouseLocked())
                    {
                        context->lockMouse();
                    }

                    context->getEventManager()->emitButtonDownEvent(event.xbutton.button > 0x07 ? event.xbutton.button - 0x04 : event.xbutton.button, event.xbutton.state, NULL);

                    break;
                case ButtonRelease:
                    if (event.xbutton.type != ButtonRelease)
                    {
                        continue;
                    }
                    if (event.xbutton.button == 0x04 || event.xbutton.button == 0x05 || event.xbutton.button == 0x06 || event.xbutton.button == 0x07)
                    {
                        continue;
                    }

                    context->getEventManager()->emitButtonUpEvent(event.xbutton.button > 0x07 ? event.xbutton.button - 0x04 : event.xbutton.button, event.xbutton.state, NULL);

                    break;
                case KeyPress:
                    if (event.xkey.type != KeyPress)
                    {
                        continue;
                    }

                    if (context->isMouseLocked() && event.xkey.keycode == 0x9)
                    {
                        context->unlockMouse();
                    }

                    context->getEventManager()->emitKeyDownEvent(event.xkey.keycode, event.xkey.state, &event.xkey);

                    break;
                case KeyRelease:
                    if (event.xkey.type != KeyRelease)
                    {
                        continue;
                    }

                    context->getEventManager()->emitKeyUpEvent(event.xkey.keycode, event.xkey.state, &event.xkey);

                    break;
                default:
                    break;
            }
        }
    }

    bool Snake::Window::isRunning()
    {
        return this->running;
    }

    void Snake::Window::start()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Window is not initialized.\n");
            return;
        }

        if (this->running)
        {
            fprintf(stderr, "Window is already running.\n");
            return;
        }

        this->running = true;

        std::thread runThread(&run, this, (Snake::X11WindowStruct*) this->windowStruct);
        runThread.detach();
    }

    void Snake::Window::stop()
    {
        if (this->destroyed)
        {
            fprintf(stderr, "Window is destroyed.\n");
            return;
        }
        if (!this->initialized)
        {
            fprintf(stderr, "Window is not initialized.\n");
            return;
        }

        if (!this->running)
        {
            fprintf(stderr, "Window is not running.\n");
            return;
        }

        this->running = false;
    }

    bool Snake::Window::isMouseLockEnabled()
    {
        return this->mouseLockEnabled;
    }

    bool Snake::Window::isMouseLocked()
    {
        return this->mouseLocked;
    }

    void Snake::Window::lockMouse()
    {
        Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

        if (XGrabPointer(windowStruct->display, windowStruct->window, true, 0, GrabModeAsync, GrabModeAsync, windowStruct->window, None, CurrentTime) == GrabSuccess)
        {
            Pixmap cursorPixmap = XCreatePixmap(windowStruct->display, windowStruct->window, 1, 1, 1);

            XColor color;
            color.red = color.green = color.blue = 0;

            Cursor blankCursor = XCreatePixmapCursor(windowStruct->display, cursorPixmap, cursorPixmap, &color, &color, 0, 0);

            XDefineCursor(windowStruct->display, windowStruct->window, blankCursor);

            XFreeCursor(windowStruct->display, blankCursor);
            XFreePixmap(windowStruct->display, cursorPixmap);

            XWarpPointer(windowStruct->display, None, windowStruct->window, 0, 0, 0, 0, this->size.width / 2, this->size.height / 2);

            this->mouseLocked = true;
        } else
        {
            this->unlockMouse();
        }
    }

    void Snake::Window::unlockMouse()
    {
        Snake::X11WindowStruct* windowStruct = (Snake::X11WindowStruct*) this->windowStruct;

        this->mouseLocked = false;

        XUngrabPointer(windowStruct->display, CurrentTime);

        XUndefineCursor(windowStruct->display, windowStruct->window);
    }
}