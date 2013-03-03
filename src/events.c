#include "events.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <string.h>

static Display * display;

static void press(int button)
{
    XEvent event;

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow) {
	event.xbutton.window = event.xbutton.subwindow;

	XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
	fprintf(stderr, "Error\n");
    }

    XFlush(display);
}

static void release(int button)
{
    XEvent event;

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow) {
	event.xbutton.window = event.xbutton.subwindow;

	XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if (XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
	fprintf(stderr, "Error\n");
    }

    XFlush(display);
}

void setup()
{
    display = XOpenDisplay(0);
}

void mouse_move(int dx, int dy)
{
    XWarpPointer(display, None, None, 0, 0, 0, 0, dx, dy);
    XFlush(display);
}

void mouse_wheel_up()
{
    press(Button4);
    release(Button4);
}

void mouse_wheel_down()
{
    press(Button5);
    release(Button5);
}

void left_mouse_button_press()
{
    press(Button1);
}

void left_mouse_button_release()
{
    release(Button1);
}

void right_mouse_button_press()
{
    press(Button3);
}

void right_mouse_button_release()
{
    release(Button3);
}
