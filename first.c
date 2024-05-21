#include "types.h"
#include "stat.h"
#include "user.h"
	
//passing command line arguments
int main(int argc, char *argv[])
{
  printf(1, "Created first system call from GFG\n");
  printf(1, "Note: Unix V6 was released in year %d\n", getyear());
  exit();
}
