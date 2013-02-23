#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ncurses.h>

#include <linux/input.h>
#include <fcntl.h>

#define VERSION 0.02
#define MOUSEFILE "/dev/input/mice"

#define LEFTCLICK 9
#define RIGHTCLICK 10

struct input_event ev;

unsigned long int mouseMovement = 0;
unsigned int leftMouseClick = 0;
unsigned int rightMouseClick = 0;


void readMouse(int fd) {
  
  if(read(fd, &ev, sizeof(struct input_event))) {

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

    mvprintw(0,0, "Left click: %d, ", leftMouseClick);
    mvprintw(1,0, "Right click: %d, ", rightMouseClick);
    mvprintw(2,0, "Mousemovement: %d ", mouseMovement);
    refresh();
  }

  return 0;
}
