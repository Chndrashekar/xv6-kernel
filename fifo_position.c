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
  int pos = fifo_position(pid);
  if(pos >= 0)
    printf(1, "Process %d is at position %d\n", pid, pos);
  else
    printf(1, "Error: The specified process %d is not in ready queue\n", pid);
  exit();
}