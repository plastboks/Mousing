/*
 * Mousing main sourcefile.
 *
 * @filename: mousing.c
 *
 * @version: 0.0.5
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


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <linux/input.h>
#include <fcntl.h>

#include "functions.h"

#define VERSION 0.05
#define MOUSEFILE "/dev/input/mice"
#define LEFTCLICK 9
#define RIGHTCLICK 10

struct input_event ev;

unsigned long int mMov = 0;
unsigned int mLC = 0;
unsigned int mRC = 0;


WINDOW *create_newwin(int height, int width, int starty, int startx) { 
  WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);
  box(local_win, 0 , 0);
  wrefresh(local_win);
  return local_win;
}


void read_mouse(int fd) {
  if(read(fd, &ev, sizeof(struct input_event))) {
    switch( ev.time.tv_sec ) {
      case LEFTCLICK:
        mLC++;
        break;
      case RIGHTCLICK :
        mRC++;
        break;
      default :
        mMov++;
    }
  }
}


void print_data(int starty, int startx) {
  int offset = 20;
  mvprintw(starty, startx + 7, "### Mousing %.2f ###", VERSION);
  mvprintw(starty + 2, startx + 2, "Left click:");
  mvprintw(starty + 2, startx + offset, "%d", mLC);
  mvprintw(starty + 3, startx + 2, "Right click:");
  mvprintw(starty + 3, startx + offset, "%d", mRC);
  mvprintw(starty + 4, startx + 2, "Movement:");
  mvprintw(starty + 4, startx + offset, "%s", commaprint(mMov));
}


void destroy_win(WINDOW *local_win) { 
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wrefresh(local_win);
  delwin(local_win);
  endwin();
  refresh();
}


int main(int argc, char *argv[]) { 
  WINDOW *my_win;

  int oldlines, oldcols, startx, starty;
  int box_height = 10;
  int box_width = 35; 

  int ch;
  int fd;
  
  if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
    perror("evdev open");
    exit(1);
  }

  initscr();
  curs_set(0);
  cbreak();
  nodelay(stdscr, true);

  starty = (LINES - box_height) / 2; 
  startx = (COLS - box_width) / 2;
  oldlines = LINES;
  oldcols = COLS;
  printw("Press Q to exit");
  refresh();
  my_win = create_newwin(box_height, box_width, starty, startx);

  do { 
    read_mouse(fd);
    if ((oldlines != LINES) || (oldcols != COLS)) {
      starty = (LINES - box_height) / 2; 
      startx = (COLS - box_width) / 2;
      oldlines = LINES;
      oldcols = COLS;
      destroy_win(my_win);
      my_win = create_newwin(box_height, box_width, starty, startx);
    }
    print_data(starty, startx);
    refresh();
  } while ((ch = getch()) != 'Q');

  endwin();
  return 0;
}
