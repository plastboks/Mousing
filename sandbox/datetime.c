#include <time.h>
#include <stdio.h>


int main() {
 
  char outstr[200];
  struct tm *local;
  time_t t;

  t = time(NULL);
  local = localtime(&t);

  strftime(outstr, sizeof(outstr), "%Y-%m-%d", local);
  
  printf("%s\n", outstr);
  return 0;
}
