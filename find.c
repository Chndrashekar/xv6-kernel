#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

static char fname[512];
static char type;
static char size_modifier;
static int size;
static int sizeFlag = 0;

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

int
strncmp(const char *p, const char *q, uint n)
{
  while(n > 0 && *p && *p == *q)
    n--, p++, q++;
  if(n == 0)
    return 0;
  return (uchar)*p - (uchar)*q;
}

int filter(int fd, struct stat st, char *name)
{
    if (strncmp(fname, name, strlen(fname)) != 0) {
      return 0;
    }

    switch (type) {
        case 'd':
            if (st.type != T_DIR)
                return 0;
            break;
        case 'f':
            if (st.type != T_FILE)
                return 0;
            break;
        default:
            break;
    }

    if (sizeFlag == 1)
    {
        switch (size_modifier) {
            case 0:
                if (st.size != size)
                    return 0;
                break;
            case '+':
                if (st.size <= size)
                    return 0;
                break;
            case '-':
                if (st.size > size)
                    return 0;
                break;
            default:
                break;
        }
    }
    return 1;
}

void
find(char *path, char *name)
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
    if (filter(fd, st, name)) {
      printf(1, "%s\n", path);
    }
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    if (filter(fd, st, fmtname(path)))
        {
            printf(1, "%s\n", buf);
        }
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (de.name[0] == '.') /* don't loop yourself to death with '.' and '..' */
                continue;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      find(buf, de.name);
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
    printf(2, "Usage: find <path> <-options> <name>\n");
    exit();
  }
  for(i=2; i<argc; i++) {
    if (!(strcmp(argv[i], "-name"))) {
        strcpy(fname, argv[i + 1]);
    } else if (!(strcmp(argv[i], "-type"))) {
        switch (argv[i + 1][0]) {
            case 'd':
                type = 'd';
                break;
            case 'f':
                type = 'f';
                break;
            default:
                printf(2, "file type unknown: %s\n", argv[i + 1]);
                exit();
        }
    } else if (!(strcmp(argv[i], "-size"))) {
      sizeFlag = 1;
        switch (argv[i + 1][0]) {
            case '+':
                size_modifier = '+';
                size = atoi(&argv[i + 1][1]);
                break;
            case '-':
                size_modifier = '-';
                size = atoi(&argv[i + 1][1]);
                break;
            default:
                size_modifier = 0;
                size = atoi(&argv[i + 1][0]);
                break;
        }
    }
  }
  find(argv[1], fmtname(argv[1]));
  exit();
}
