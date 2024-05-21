#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int x,z;
#ifdef PRIORITY
  printf(1, "\nPRIORITY SCHEDULER----------");
  printf(1, "\n\nset_sched_priority test----------------\n\n");
  set_sched_priority(0);
  printf(1, "Parent process %d priority set to 0\n", getpid());
#endif
#ifdef FCFS
  printf(1, "\nFCFS SCHEDULER----------");
#else
  #ifndef PRIORITY
    printf(1, "\nDEFAULT SCHEDULER----------");
  #endif
#endif
  int pid = fork();
  if (pid == 0) {
    pid = getpid();
#ifdef PRIORITY
    printf(1, "Child process %d priority set to 0\n", pid);
    set_sched_priority(0);
#endif
    for(z = 0; z < 4000000000; z+=1)
        x = x + 3.14*89.64;
    exit();
  }
  sleep(2);
  int pid2 = fork();
  if (pid2 == 0) {
    pid2 = getpid();
#ifdef PRIORITY
    printf(1, "Child process %d priority set to 1\n", pid2);
    set_sched_priority(1);
#endif
    for(z = 0; z < 4000000000; z+=1)
        x = x + 3.14*89.64;
    exit();
  }
  sleep(2);
  int pid3 = fork();
  if (pid3 == 0) {
    pid3 = getpid();
    for(z = 0; z < 4000000000; z+=1)
        x = x + 3.14*89.64;
    exit();
  }
  sleep(2);
  int pid4 = fork();
  if (pid4 == 0) {
    pid4 = getpid();
    for(z = 0; z < 4000000000; z+=1)
        x = x + 3.14*89.64;
    exit();
  }
  
  sleep(500);
  printf(1, "\n\nProc dump-------------------\n\n");
  cps();
  printf(1, "\n\ntime_scheduled test-------------------\n\n");
  printf(1, "Process time_scheduled\n");
  int ticks = time_scheduled(pid);
  if(ticks >= 0)
    printf(1, "%d \t %d\n", pid, ticks);
  else
    printf(1, "Error: unable to get time scheduled for process %d\n", pid);

  ticks = time_scheduled(pid2);
  if(ticks >= 0)
    printf(1, "%d \t %d\n", pid2, ticks);
  else
    printf(1, "Error: unable to get time scheduled for process %d\n", pid2);
  ticks = time_scheduled(pid3);
  if(ticks >= 0)
    printf(1, "%d \t %d\n", pid3, ticks);
  else
    printf(1, "Error: unable to get time scheduled for process %d\n", pid3);
  ticks = time_scheduled(pid4);
  if(ticks >= 0)
    printf(1, "%d \t %d\n", pid4, ticks);
  else
    printf(1, "Error: unable to get time scheduled for process %d\n", pid4);
  
#ifdef FCFS
  printf(1, "\nfifo_position Test-----------------\n\n");
  printf(1, "Process fifo_position\n");
  printf(1, "%d \t %d\n", pid, fifo_position(pid));
  printf(1, "%d \t %d\n", pid2, fifo_position(pid2));
  printf(1, "%d \t %d\n", pid3, fifo_position(pid3));
  printf(1, "%d \t %d\n", pid4, fifo_position(pid4));
#endif
#ifdef PRIORITY
  printf(1, "\nget_sched_priority Test--------------------------\n\n");
  printf(1, "Process get_sched_priority\n");
  printf(1, "%d \t %d\n", pid, get_sched_priority(pid));
  printf(1, "%d \t %d\n", pid2, get_sched_priority(pid2));
  printf(1, "%d \t %d\n", pid3, get_sched_priority(pid3));
  printf(1, "%d \t %d\n\n", pid4, get_sched_priority(pid4));
#endif
  kill(pid);
  kill(pid2);
  kill(pid3);
  kill(pid4);

  exit();
}
