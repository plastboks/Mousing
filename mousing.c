/*
 * Mousing main file.
 *
 * @filename: mousing.c
 *
 * @version: 0.0.3
 *
 * @date: 2013-02-24
 *
 * @description: Mousing main program file
 *
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


int main() {
  int fd;
  initscr();
  curs_set(0);

  if ((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
    perror("evdev open");
    exit(1);
  }

  while (true) { 
    readMouse(fd);

    mvprintw(0,0, "Left click: %d, ", mLC);
    mvprintw(1,0, "Right click: %d, ", mRC);
    mvprintw(2,0, "Mousemovement: %d ", mMov);
    refresh();
  }
  return 0;
}
