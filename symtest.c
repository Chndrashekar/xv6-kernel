#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
  char buffer[51];

  if(argc != 3) {
    printf(1, "Usage: %s target_path symlink_path\n", argv[0]);
    exit();
  }

  char* target = argv[1];
  char* symlink_path = argv[2];

  int result = symlink(target, symlink_path);
  if(result == -1) {
    printf(1, "Error creating symlink %s -> %s\n", symlink_path, target);
    exit();
  }

  printf(1, "Created symlink %s -> %s\n\n", symlink_path, target);

  int fd = open(symlink_path, O_RDONLY | O_NOFOLLOW);
  if (fd == -1) {
    printf(1, "W: Open NOFOLLOW failed for \"%s\" as expected\n\n", symlink_path);
  } else {
    printf(1, "E: Open NOFOLLOW succeeded for %s! Unexpected\n", symlink_path);
    exit();
  }

  fd = open(target, O_RDONLY | O_NOFOLLOW);
  printf(1, "Opened file %s\n", target);

  int bytes_read = read(fd, buffer, 50);
  if (bytes_read != 50) {
      printf(1, "read failed\n");
      exit();
  }
  buffer[bytes_read] = '\0'; // null-terminate the string

  printf(1, "Printing %d bytes from the file: \n\n%s\n", bytes_read, buffer);
  close(fd);

  exit();
}
