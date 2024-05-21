#include "types.h"
#include "stat.h"
#include "user.h"
	
//passing command line arguments
int main(int argc, char *argv[])
{
  int pid;
  if (argc < 2) {
    pid = getpid();
  } else {
    pid = atoi(argv[1]);
  }
  int ticks = time_scheduled(pid);
  if(ticks >= 0)
    printf(1, "Process %d has been scheduled for %d ticks\n", pid, ticks);
  else
    printf(1, "Error: unable to get time scheduled for process %d\n", pid);
  exit();
}