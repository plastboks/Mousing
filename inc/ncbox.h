/*
 * Mousing ncbox.h file
 *
 * @filename: ncbox.h
 *
 * @version: 0.0.1
 *
 * @date: 2013-03-04
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

WINDOW *create_newwin(int height, int width, int starty, int startx);
void print_data(int starty, int startx, int m_y, int m_x, unsigned int mask_r, unsigned int m_o);
void destroy_win(WINDOW *local_win);
void my_setup();
void my_colors();
