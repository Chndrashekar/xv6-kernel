#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int x,z;
  int pid = fork();

  if (pid == 0) {
    for(z = 0; z < 4000000000; z+=1)
        x = x + 3.14*89.64;
  }
  int pid2 = fork();
  if (pid2 == 0) {
    for(z = 0; z < 4000000000; z+=1)
        x = x + 3.14*89.64;
  }

  int pid3 = fork();
  if (pid3 == 0) {
    for(z = 0; z < 4000000000; z+=1)
        x = x + 3.14*89.64;
  }

  while (wait() != -1);

  exit();
}
