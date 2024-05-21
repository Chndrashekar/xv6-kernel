#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "param.h"

#define BUF_SIZE 512
//#define BLOCKS 16523

char buf[BUF_SIZE];

int main(int argc, char *argv[]) {
  int fd, i, n;

  if (argc < 2) {
    printf(1, "Usage: large NUM_BLOCKS\n");
    exit();
  }

  int blocks = atoi(argv[1]);

  unlink("large_file");
  fd = open("large_file", O_CREATE | O_WRONLY);
  if (fd < 0) {
    printf(2, "Failed to open file\n");
    exit();
  }

  for (i = 0; i < blocks; i++) {
    n = write(fd, buf, BUF_SIZE);
    if (n != BUF_SIZE) {
      printf(2, "Ran out of disk space!\nFileSystem Size: %d\n", FSSIZE);
      exit();
    }
  }
  
  close(fd);
  exit();
}
