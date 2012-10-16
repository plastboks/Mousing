#include <stdlib.h>
#include <stdio.h>   
#include <linux/input.h>
#include <fcntl.h>    


int main(int argc, char **argv) {
  unsigned long mouseMovement = 0;

  int fd;
  if ((fd = open("/dev/input/mice", O_RDONLY)) < 0) {
    perror("evdev open");
    exit(1);
  }

  struct input_event ev;

  while(1) {
    if (read(fd, &ev, sizeof(struct input_event))) {
      mouseMovement++;
    }
    printf("Length: %lu \r", mouseMovement);
    fflush(stdout);
  }

  return 0;

}

