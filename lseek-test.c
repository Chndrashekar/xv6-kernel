#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
  int fd;
  char buf[50];

  // Open a file for read and write access, creating it if it doesn't exist
  // Use "file" if no filename is given, otherwise use the given filename
  if(argc != 2) fd = open("file", O_CREATE | O_RDWR);
  else fd = open(argv[1], O_RDWR | O_CREATE);

  if(fd < 0){
    printf(1, "%s: cannot open %s\n", argv[0], argv[1]);
    exit();
  }

  // Write "hello" to the file
  write(fd, "hello", 5);

  // Set the file offset to the beginning of the file
  if (lseek(fd, 0, SEEK_SET) == -1) {
    printf(1, "Invalid offset\n");
    exit();
  }

  // Write "Hola World!" and "\n012345678" to the file
  write(fd, "Hola World!", 11);
  write(fd, "\n012345678", 10);

  // Set the file offset to the 15th byte (right after "\n012")
  if (lseek(fd, 15, SEEK_SET) == -1) {
    printf(1, "Invalid offset\n");
    exit();
  }

  // Overwrite text after "\n012" with "Hello again!"
  write(fd, "\n\nHello again!", 14);

  // Set the file offset to the beginning of the file
  if (lseek(fd, 0, SEEK_SET) == -1) {
    printf(1, "Invalid offset\n");
    exit();
  }

  // Read up to 50 bytes from the file and store in buf
  read(fd, buf, 50);

  // Print the contents of buf to the console
  printf(1, "%s\n", buf);

  // Close the file and exit the program
  close(fd);
  exit();
}