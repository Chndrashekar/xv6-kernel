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
    int pid1, pid2, pid3;
    int priority1 = 0; // highest priority
    int priority2 = 1;
    int priority3 = 2; // lowest priority
    struct mutex m;

    init_mutex(&m);

    // create three processes with different priorities
    pid1 = fork();
    if (pid1 == 0) {
        set_sched_priority(priority1);
        acquire_mutex(&m);
        printf(1, "Process 1 with priority %d\n", get_sched_priority(getpid()));
        release_mutex(&m);
    }

    pid2 = fork();
    if (pid2 == 0) {
        set_sched_priority(priority2);
        acquire_mutex(&m);
        printf(1, "Process 2 with priority %d\n", get_sched_priority(getpid()));
        release_mutex(&m);
    }

    pid3 = fork();
    if (pid3 == 0) {
        set_sched_priority(priority3);
        acquire_mutex(&m);
        printf(1, "Process 3 with priority %d\n", get_sched_priority(getpid()));
        release_mutex(&m);
    }

    while (wait() != -1);

    exit();
}
