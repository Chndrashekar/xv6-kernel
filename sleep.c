#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
  int sleep_sec;
  if (argc < 2){
    printf(2, "Usage: sleep NUMBER\n\
Pause for NUMBER of ticks and the NUMBER should be an integer. \n\
Given an argument \"NUMBER\", pause for the amount of time\n\
specified by the NUMBER\n");
    exit();
  }

  sleep_sec = atoi(argv[1]);
  if (sleep_sec > 0){
    sleep(sleep_sec);
  } else {
    printf(2, "Invalid interval %s\n", argv[1]);
  }
  exit();
}
