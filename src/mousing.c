/*
 * Mousing main sourcefile.
 *
 * @filename: mousing.c
 *
 * @version: 0.0.7
 *
 * @date: 2013-02-24
 *
 * @description: Mousing main program file
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

// a litte usleep fix
#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "x11mouse.h"
#include "ncbox.h"

#define VERSION 0.07


void interval_increment(int *interval) {
  *interval += 1;
  if (*interval > pow(2,14)) {
    *interval = 1;
  }
}


int main(int argc, char *argv[]) { 
  WINDOW *my_win;

  int oldlines, oldcols, sX, sY, mX, mY, ch;
  int interval = 0;
  int box_height = 10;
  int box_width = 35; 
  int hold_time = pow(2,15);
  unsigned int mR, mO;

  x11read_init();
  my_setup();
  my_colors();

  sY = (LINES - box_height) / 2; 
  sX = (COLS - box_width) / 2;
  oldlines = LINES;
  oldcols = COLS;

  printw("Press Q to exit. Version: %.2f", VERSION);
  refresh();
  my_win = create_newwin(box_height, box_width, sY, sX);

  do { 

    x11read_mouse(&interval, &mX, &mY, &mO, &mR);
    if ((oldlines != LINES) || (oldcols != COLS)) {
      sY = (LINES - box_height) / 2; 
      sX = (COLS - box_width) / 2;
      oldlines = LINES;
      oldcols = COLS;
      destroy_win(my_win);
      my_win = create_newwin(box_height, box_width, sY, sX);
    }
    print_data(sY, sX, mY, mX, mR, mO);
    refresh();

    usleep(hold_time);
    interval_increment(&interval);

  } while ((ch = getch()) != 'q');

  endwin();
  free(root_windows);
  return 0;
}
