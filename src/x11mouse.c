/*
 * Mousing x11mouse sourcecode file
 *
 * @filename: x11mouse.c
 *
 * @version: 0.0.2
 *
 * @date: 2013-11-07
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

/**
 * Error handler.
 *
 * @display:    Display pointer.
 * @event:      XErrorEvent pointer.
 *
 * Returns true if errors.
 */
static int _XlibErrorHandler(Display *display, XErrorEvent *event)
{
    fprintf(stderr, "An error occured detecting the mouse position\n");
    return True;
}

/**
 * Setup x11 window.
 *
 * Returns nothing.
 */
void x11read_init()
{
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

/**
 * Read X11 mouse.
 *
 * @pos[]:          int pos [x,y] for mouse.
 * @click[]:        unsigned int [left, middle, right] clicks for mouse.
 * @state[]:        unsigned int [current, old] (mask_return).
 * @movement:       unsigned int* pointer mouse movement.
 *
 * Returns nothing.
 */
void x11read_mouse(int pos[],
                   unsigned int click[],
                   unsigned int state[],
                   unsigned int *movement
                   )
{

    int i, mov_y, mov_x;
    int old_mouse_x = pos[0];
    int old_mouse_y = pos[1];

    /* Read the mouse values */
    for (i = 0; i < number_of_screens; i++) {
        result = XQueryPointer(display,
                               root_windows[i],
                               &window_returned,
                               &window_returned,
                               &pos[0],
                               &pos[1],
                               &win_x,
                               &win_y,
                               &state[0]);
        if (result == True) {
            break;
        }
    }

    /* No mouse found. */
    if (result != True) {
        fprintf(stderr, "No mouse found.\n");
    }

    /**
     * Calculate the movement relative to changes in
     * mouse pos x and mouse pos y.
     * Add up and increment the movment integer.
     */
    if (old_mouse_x != pos[0] || old_mouse_y != pos[1]) {
        if (old_mouse_x > pos[0]) {
            mov_x = old_mouse_x - pos[0];
        } else {
            mov_x = pos[0] - old_mouse_x;
        }

        if (old_mouse_y > pos[1]) {
            mov_y = old_mouse_y - pos[1];
        } else {
            mov_y = pos[1] - old_mouse_y;
        }
        *movement += mov_y + mov_x;
    }

    /**
     * Increment mouse clicks
     */

    /* right click */
    if ((state[0] == 1024) && (state[1] == 0)) {
        click[2]++;
        state[1] = 1;
    }
    /* left click */
    if ((state[0] == 256) && (state[1] == 0)) {
        click[0]++;
        state[1] = 1;
    }
    /* middle click */
    if ((state[0] == 512) && (state[1] == 0)) {
        click[1]++;
        state[1] = 1;
    }
    /**
     * Upon mouse button key up reset the state byte.
     * This to prevent more than one record to be saved 
     * to the database if mouse button has a long key down.
     */
    if (state[0] == 0) {
        state[1] = 0;
    }

}
