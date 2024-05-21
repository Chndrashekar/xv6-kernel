#include "types.h"

#include "stat.h"

#include "user.h"

char buf[512];

void
head(int fd, char * name, int line) {
    int i, n; //here the size of the read chunk is defined by n, and i is used to keep a track of the chunk index
    int l, c; // here line number is defined by l, and the character count in the string is defined by c

    l = c = 0;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        for (i = 0; i <= n; i++) { //print the characters in the line 
            if (buf[i] != '\n') {
                printf(1, "%c", buf[i]);
            }
            //if the number of lines is equal to l, then exit
            else if (l == (line - 1)) {
                printf(1, "\n");
                exit();
            }
            //if the number of lines is not equal to l, then jump to next line and increment the value of l 
            else {
                printf(1, "\n");
                l++;
            }
        }
    }

    if (n < 0) {
        printf(1, "head: read error\n");
        exit();
    }
}

int
main(int argc, char * argv[]) {
    int i;
    int fd = 0; // when the file is not specified, then it will take input from the user
    int x = 10; // will read the first 10 lines by default
    char * file; // pointer to the name of the file
    char a;

    file = ""; // in the case when no file name is specified, it will take input from the user

    if (argc <= 1) {
        head(0, "", 10); // handles the default case of taking input from user for 10 lines
        exit();
    } else {
        for (i = 1; i < argc; i++) {
            a = * argv[i]; // assigns the char value of the argv to the var a

            if (a == '-') { // it means that -NUM is provided, hence limited number of lines are to be printed
                argv[i]++;
                x = atoi(argv[i]++);
            } else { // if a !='-' then it implies that number of lines are not defined and hence default lines will print
                if ((fd = open(argv[i], 0)) < 0) { // this will execute if the file is unable to open
                    printf(1, "head: cannot open %s\n", argv[i]);
                    exit();
                }
            }
        }

        head(fd, file, x);
        close(fd);
        exit();

    }
}