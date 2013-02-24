/*
 * Mousing main sourcefile.
 *
 * @filename: mousing.c
 *
 * @version: 0.0.3
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

#define VERSION 0.0.3
#define MOUSEFILE "/dev/input/mice"
#define LEFTCLICK 9
#define RIGHTCLICK 10

struct input_event ev;

unsigned long int mMov = 0;
unsigned int mLC = 0;
unsigned int mRC = 0;


void readMouse(int fd) {
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


void printState(int fd) {
  readMouse(fd);
  mvprintw(0,0, "Left click: %d, ", mLC);
  mvprintw(1,0, "Right click: %d, ", mRC);
  mvprintw(2,0, "Mousemovement: %d ", mMov);
  refresh();
}


int main() {
  int fd;
  
  if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
    perror("evdev open");
    exit(1);
  }

  initscr();
  curs_set(0);

  while (true) { 
    printState(fd);
  }

  return 0;
}
