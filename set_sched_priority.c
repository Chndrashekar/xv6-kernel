#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
  int priority;
  if (argc < 2) {
    priority = 2;
  } else {
    priority = atoi(argv[1]);
  }
  int ret = set_sched_priority(priority);
  if(ret == 0)
    printf(1, "Process %d is at priority %d\n", getpid(), priority);
  else
    printf(1, "Error: The specified priority %d is invalid\n", priority);
  exit();
}
