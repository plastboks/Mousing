#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ncurses.h>

#include <linux/input.h>
#include <fcntl.h>


#define VERSION 0.01
#define MOUSEFILE "/dev/input/mice"

#define LEFTCLICK 9
#define RIGHTCLICK 10


int main() {

  unsigned long int mouseMovement = 0;
  unsigned int leftMouseClick = 0;
  unsigned int rightMouseClick = 0;
  int fd;

  initscr();
  curs_set(0);

  struct input_event ev;

  if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
    perror("evdev open");
    exit(1);
  }

  while(read(fd, &ev, sizeof(struct input_event))) {

    switch( ev.time.tv_sec ) {
      case LEFTCLICK:
        leftMouseClick++;
        break;
      case RIGHTCLICK :
        rightMouseClick++;
        break;
      default :
        mouseMovement++;
    }

    printw("Left click: %d, ", leftMouseClick);
    printw("Right click: %d, ", rightMouseClick);
    printw("Movement:  %d \r", mouseMovement);
    refresh();
  }

  return 0;
}

