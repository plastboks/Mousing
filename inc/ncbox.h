/*
 * Mousing ncbox.h file
 *
 * @filename: ncbox.h
 *
 * @version: 0.0.2
 *
 * @date: 2013-11-07
 *
 * @description: Mousing ncurses box header file
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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <fcntl.h>

WINDOW *create_newwin(int box_dim[][2], int starty, int startx, int screen);
void print_mouse_data(int cords[], int pos[], unsigned int clicks[], unsigned int mMov);
void print_mouse_stats(int cords[]);
void print_mousing_help(int cords[]);
void destroy_win(WINDOW *local_win);
void cord_update(int cords[], int old_cords[], int box_dim[][2], int screen);
void my_setup();
void my_colors();
