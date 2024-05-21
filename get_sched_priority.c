#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
  int pid;
  if (argc < 2) {
    pid = getpid();
  } else {
    pid = atoi(argv[1]);
  }
  int priority = get_sched_priority(pid);
  if(priority != -1)
    printf(1, "Process %d is priority is %d\n", pid, priority);
  else
    printf(1, "Error: The specified pid %d is not in ready queue\n", pid);
  exit();
}
