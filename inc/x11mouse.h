/*
 * Mousing x11mouse.h file
 *
 * @filename: x11mouse.h
 *
 * @version: 0.0.1
 *
 * @date: 2013-03-04
 *
 * @description: Mousing x11mouse read file
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

#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int number_of_screens;
Bool result;
Window *root_windows;
Window window_returned;
Display *display;
int win_x, win_y;

void x11read_init();
void x11read_mouse(int *mouse_x, int *mouse_y, unsigned int *mask_return);
