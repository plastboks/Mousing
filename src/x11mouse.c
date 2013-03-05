/*
 * Mousing x11mouse sourcecode file
 *
 * @filename: x11mouse.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-03-04
 *
 * @description: Mousings x11mouse sourcecode file
 *
 * This file is part of Mousing.
 *
 * Mousing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mousing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mousing.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "x11mouse.h"


static int _XlibErrorHandler(Display *display, XErrorEvent *event) {
    fprintf(stderr, "An error occured detecting the mouse position\n");
    return True;
}


void x11read_init() {
  int i; 
  XSetErrorHandler(_XlibErrorHandler);
  display = XOpenDisplay(NULL);
  assert(display);
  number_of_screens = XScreenCount(display);
  root_windows = malloc(sizeof(Window) * number_of_screens);
  
  for (i = 0; i < number_of_screens; i++) {
    root_windows[i] = XRootWindow(display, i);
  }
}


void x11read_mouse(int *mouse_x, int *mouse_y, unsigned int *movement, unsigned int *mask_return) {
  int i;
  int old_mouse_x = *mouse_x;
  int old_mouse_y = *mouse_y;
  int mov_y, mov_x;

  for (i = 0; i < number_of_screens; i++) {
    result = XQueryPointer(display, root_windows[i], &window_returned,
      &window_returned, mouse_x, mouse_y, &win_x, &win_y,
      mask_return);
    if (result == True) {
      break;
    }
  }

  if (old_mouse_x != *mouse_x || old_mouse_y != *mouse_y) {
    if (old_mouse_x > *mouse_x) {
      mov_x = old_mouse_x - *mouse_x;
    } else {
      mov_x = *mouse_x - old_mouse_x;
    }

    if (old_mouse_y > *mouse_y) {
      mov_y = old_mouse_y - *mouse_y;
    } else {
      mov_y = *mouse_y - old_mouse_y;  
    }
    *movement += mov_y + mov_x;
  }

  if (result != True) {
    fprintf(stderr, "No mouse found.\n");
  }

}
