#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int readLine(int fd, char *line, int n)
{
	char c;
	int count = 0;
	while(read(fd, &line[count], 1))
	{
        if(line[count] == '\n')
        { 
			count--;
            //line[count]='\0';
			break;
        }
		count += 1;
	}
	line[count] = '\0';
    return count; 
}

void execComm(char * cmd) {
	char * commlist[255];
	int x = 0;
	int y = 0;
	
	commlist[0] = malloc(sizeof(char) * 255);
	for(int i=0; i<=strlen(cmd); i++) {
		if(cmd[i] == ' ' || cmd[i] == '\0') {
			if(y==0) {continue;}
			commlist[x][y] = '\0';
			y = 0;
			x += 1;
			commlist[x] = malloc(sizeof(char) * 255);
			continue;
		}
		commlist[x][y] = cmd[i];
		y += 1;
	}
	
	commlist[x] = '\0';
	printf("\n");
	
	
	int pid = fork();
	
	if(pid == 0) {
		execvp(commlist[0], commlist);
		exit(0);
	} else {
		int ex;
		wait(&ex);
	}
	
}

void exec(char * l)
{
	char *token;
	char d[2] = ";";
	char twod[255][255];
	
	token = strtok(l,d);
	
	while (token != NULL) {
		execComm(token);
		token = strtok(NULL,d);
	}
}


int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Invalid arguments");
        exit(0);
    }
    int count;
    char l[255];
    int fd = open(argv[1], O_RDONLY);
    while((count = readLine(fd, l, 0)) != 0)
    {
		exec(l);
		strcpy(l, "");
    }
}