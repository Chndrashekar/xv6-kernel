#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "x86.h"

struct mutex {
  uint locked;
};

void
init_mutex(struct mutex *m)
{
  m->locked = 0;
}

void
acquire_mutex(struct mutex *m)
{
  while(xchg(&m->locked, 1) != 0)
    ;
}

void
release_mutex(struct mutex *m)
{
  xchg(&m->locked, 0);
}

int
main(int argc, char *argv[])
{
  int i, pid, pos;
  struct mutex m;

  init_mutex(&m);

  for (i = 0; i < 10; i++) {
    pid = fork();
    if (pid == 0) {
      // child process
      acquire_mutex(&m);
      printf(1, "Child %d started\n", i);
      release_mutex(&m);
      pos = fifo_position(getpid());
      acquire_mutex(&m);
      printf(1, "Child %d position: %d\n", i, pos);
      release_mutex(&m);
      //sleep(300); // do some work
      int z, x=0;
      for(z = 0; z < 4000000000; z+=1)
        x = x + 3.14*89.64; //Useless calculation to consume CPU Time
      acquire_mutex(&m);
      printf(1, "Child %d finished\n", i);
      release_mutex(&m);
      exit();
    } else if (pid < 0) {
      printf(1, "fork failed\n");
      exit();
    }
  }

  // parent process
  while (wait() != -1); // wait for all child processes to exit

  exit();
}