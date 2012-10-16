#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <linux/input.h>
#include <fcntl.h>    

#define VERSION 0.01


int main(int argc, char **argv) {
  unsigned long mouseMovement = 0;
  int fd;

  initscr();

  if ((fd = open("/dev/input/mice", O_RDONLY)) < 0) {
    perror("evdev open");
    exit(1);
  }

  struct input_event ev;

  while(1) {
    if (read(fd, &ev, sizeof(struct input_event))) {
      mouseMovement++;
      printw("Length: %lu \r", mouseMovement);
      refresh();
    }
  
  }

  return 0;

}

