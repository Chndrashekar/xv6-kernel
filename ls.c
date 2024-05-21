#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

static int all;

void
fmtname(char *path, struct stat st)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  //if(strlen(p) >= DIRSIZ)
  //  return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));

  // Add '/' at the end of directory name no matter the length of the name.
  if (st.type == T_DIR) {
    buf[strlen(p)] = '/';
  }

  // Ignore . and .. dirs
  /*if ((buf[0] == '.') &&
    (buf[1] != '/') && !((buf[1] == '.') && buf[2] == '/')
     && !all) {
    return;
  }*/

  if ((buf[0] == '.') && !all) {
    return;
  }

  printf(1, "%s %d %d %d\n", buf, st.type, st.ino, st.size);
  return;
}

void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    fmtname(path, st);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      fmtname(buf, st);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit();
  }

  if((argc == 2) && !(strcmp(argv[1], "-a"))) {
    all = 1;
    ls(".");
    exit();
  }

  for(i=1; i<argc; i++) {
    if (!(strcmp(argv[i], "-a"))) {
      all = 1;
    }
  }
  for(i=1; i<argc; i++) {
    if (!(strcmp(argv[i], "-a"))) {
      continue;
    }
    ls(argv[i]);
  }
    
  exit();
}
