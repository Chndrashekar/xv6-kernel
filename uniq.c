#include "types.h"
#include "stat.h"
#include "user.h"

const int BUFFER_SIZE = 1024;

int compare(char*a1, char*a2) {
	int i=0;
	while(a1[i] != '\0') {
		int c = a1[i] - a2[i];
		if(c != 0 && c != 32 && c!= -32)
			return 1;
		i++;
	}
	if(a2[i]!='\0')
		return 1;
	return 0;
}

void uniq(int fd, char type) {
	int i=0, t, count=0, num=0, rep_count=1;
	char line[BUFFER_SIZE];
	char prev[BUFFER_SIZE];
	
	char* p = (char*) malloc (BUFFER_SIZE*sizeof(char));
	if(fd<0) {
		printf(1,"Unexpected error\n");
		exit();
	}
	t = read(fd,p,BUFFER_SIZE);
	p[t] = '\0';
	i=0;
	while(p[i]!='\0') {
		count=0;
		while(p[i]!= '\n') {
			line[count] = p[i];
			count++;
			i++;
		}
		
		line[count] = '\0';
		i++;
		strcpy(prev, line);
		while(p[i] != '\0') {
			count=0;
			
			while(p[i] != '\n') {
				line[count] = p[i];
				i++;
				count++;
			}
			line[count] = '\0';
			i++;
			switch(type) {
				case 'c':
					if(strcmp(prev,line)!=0) {
						printf(1,"%d, %s\n",rep_count,prev);
						strcpy(prev,line);
						rep_count = 1;
					}
					else 
						rep_count++;
					num++;
					break;
				case 'i':
					if(compare(prev,line)!=0) {
						printf(1," %s\n",prev);
						strcpy(prev,line);
					}
					num++;
					break;
				case 'd':
					if(strcmp(prev,line)!=0) {
						if(rep_count>1)
							printf(1,"%s\n",prev);
						strcpy(prev,line);
						rep_count = 1;
					}
					else
						rep_count++;
					num++;
					break;
				default:
					if(strcmp(prev,line)!=0) {
						printf(1," %s\n",prev);
						strcpy(prev,line);
					}
					num++;
			}
		}
		if (type == 'c')
			printf(1,"%d,%s\n",rep_count,prev);
		else if (type == 'd') {
			if(rep_count > 1)
				printf(1,"%s\n",prev);
		} else
			printf(1," %s\n",prev);
	}
	exit();	
}

int main(int argc, char *argv[]){
	int fd = 0;
	char type = 'n';
	if (argc > 1) {
		int i;
		for(i=1; i<argc; i++) {
			if (!(strcmp(argv[i], "-c"))) {
				type = 'c';
			} else if (!(strcmp(argv[i], "-d"))) {
				type = 'd';
			} else if (!(strcmp(argv[i], "-i"))) {
				type = 'i';
			} else {
				if (argv[i][0] == '-') {
					printf(1,"Error: Invalid argument %s\n", argv[i]);
					printf(2, "Usage: uniq <-option> <name>\nOptions allowed: -c -i -d\n");
					exit();
				}
				fd = open(argv[i],0);
			}
		}
	}
	uniq(fd, type);
	close(fd);
}