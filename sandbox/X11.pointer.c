/*
 * A simple X11 mousepos/state outputter. Helpful for debugging.
 *
 * @filename: X11.pointer.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-03-04
 *
 * @description: a simple X11 mousepos/state outputter.
 *
 * Compile with: gcc X11.pointer.c -o X11.pointer -lX11
 *
 */

#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>


static int _XlibErrorHandler(Display *display, XErrorEvent *event) {
    fprintf(stderr, "An error occured detecting the mouse position\n");
    return True;
}

int main(void) {
 
    int number_of_screens;
    int i;
    int readings = 0;
    Bool result;
    Window *root_windows;
    Window window_returned;
    int mouse_x, mouse_y;
    int win_x, win_y;
    int mask_return;

    Display *display = XOpenDisplay(NULL);
    assert(display);
    XSetErrorHandler(_XlibErrorHandler);
    number_of_screens = XScreenCount(display);
    root_windows = malloc(sizeof(Window) * number_of_screens);
    
    for (i = 0; i < number_of_screens; i++) {
        root_windows[i] = XRootWindow(display, i);
    }
    
    while (1) {
      readings ++;

      for (i = 0; i < number_of_screens; i++) {
        result = XQueryPointer(display, root_windows[i], &window_returned,
            &window_returned, &mouse_x, &mouse_y, &win_x, &win_y,
            &mask_return);
        if (result == True) {
          break;
        }
      }
      
      if (result != True) {
        fprintf(stderr, "No mouse found.\n");
        return -1;
      }
      printf("Mouse is at (%d,%d), mousestate is :%d, reading: %d\n", mouse_x, mouse_y, mask_return, readings);

      // wait a bit before next itteration.
      usleep(20000);
    }
    free(root_windows);
    return 0;
}
