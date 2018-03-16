//2014037756 컴퓨터공학과 구수연

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

pid_t pid;

void split(char* line);
void run(char *cmd);
int background=0, hisCount=0;
char history[20][1024];

int main()
{
	char input[1024], pathbuf[255];
	while (1) {
		getcwd(pathbuf,255);
		printf("%s$ ",pathbuf);
		fflush(NULL);
 
		if (!fgets(input, 1024, stdin)){
			perror("input size over!\n");
			return 0;
		}
			
		input[strlen(input)-1] = '\0';
		char *check, *cptr;
		char *line, *ptr;
		check = strtok_r(input, "\0", &cptr);
		
		if(!strcmp("!!", check)){
			line = strtok_r(history[hisCount-1], ";", &ptr);
			split(line);
		} else if (!strcmp("!2", check)) {
			line = strtok_r(history[hisCount-2], ";", &ptr);
			split(line);
		} else {
			sprintf(*(history+hisCount), "%s", input);
			hisCount++;
			
			line = strtok_r(input, ";", &ptr);
			split(line);
			while((line=strtok_r(NULL, ";", &ptr)) != NULL)
			split(line);
		}
	}
	
	return 0;
}


void split(char* line)
{
	char temp[1024];
	strcpy(temp,line);
	
	char *cmd, *ptr;
	int pipeCount, fds[20][2], i, j;
	
	if(strstr(temp,"|")){
		pipeCount = 0;
		cmd = strtok_r(temp, "|", &ptr);
		while((cmd=strtok_r(NULL, "|", &ptr)) != NULL)
            pipeCount++;
            
		cmd = strtok_r(line, "|", &ptr);
		int pids[pipeCount];
		for(i=0; i<pipeCount+1; i++){
			pipe(fds[i]);
			if((pids[i]=fork()) == 0){
				if (i == pipeCount) {
					close(STDIN_FILENO);
                    dup(fds[i-1][0]);
                    close(fds[i][1]);
                }
                else if (i == 0) {
                    close(fds[i][0]);
                    close(STDOUT_FILENO);
                    dup(fds[i][1]);
                }
                else {
                    close(STDIN_FILENO);
                    dup(fds[i-1][0]);
                    close(STDOUT_FILENO);
                    dup(fds[i][1]);
                }
                for (j=0; j<i; j++) {
                    close(fds[j][0]);
                    close(fds[j][1]);
                }
                run(cmd);
                exit(0);
			} else {
				for (j=0; j<i; j++) {
                    close(fds[j][0]);
                    close(fds[j][1]);
                }
                waitpid(pids[i], NULL, 0);
			} cmd = strtok_r(NULL, "|", &ptr);
		}
	} else {
		run(temp);
	}
}



void run(char *cmd) {
	char temp[1024];
	strcpy(temp, cmd);
	
	char *ptr, *token, *redirect;
	char **cmdElem = (char **)malloc(sizeof(char)*1024);
	*cmdElem = strtok_r(temp, " ", &ptr);
	
	int fd, redirectNum=0, cmdElemCount=1;
	
	if (!strcmp("cd", *cmdElem)) {
        *cmdElem = strtok_r(NULL, " ", &ptr);
        chdir(*cmdElem);
    } else {
		while((token=strtok_r(NULL, " ", &ptr)) != NULL) {
            if (!strcmp(">", token)) {
				redirectNum = 1;
				redirect = strtok_r(NULL, " ", &ptr);
			} else if (!strcmp("<", token)) {
				redirectNum = 2;
				redirect = strtok_r(NULL, " ", &ptr);
			} else if (!strcmp(">>", token)) {
				redirectNum = 3;
				redirect = strtok_r(NULL, " ", &ptr);
			} else if (!strcmp(">!", token)) {
				redirectNum = 4;
				redirect = strtok_r(NULL, " ", &ptr);
			} else if (!strcmp("&", token)) {
				redirectNum = 5;
				background = 1;
			} else {
				*(cmdElem + cmdElemCount) = token;
			}cmdElemCount++;
		}
		
		if((pid=fork()) == 0){
			switch(redirectNum){
				case 1:
					fd = open(redirect, O_CREAT|O_EXCL|O_WRONLY, 0644);
					close(STDOUT_FILENO);
					dup(fd);
					close(fd);
					break;
				case 2:
					fd = open(redirect, O_RDONLY, 0644);
					close(STDIN_FILENO);
					dup(fd);
					close(fd);
					break;
				case 3:
					fd = open(redirect, O_CREAT|O_APPEND|O_WRONLY, 0644);
					close(STDOUT_FILENO);
					dup(fd);
					close(fd);
					break;
				case 4:
					fd = open(redirect, O_TRUNC|O_WRONLY, 0644);
					close(STDOUT_FILENO);
					dup(fd);
					close(fd);
					break;
			}redirectNum=0;
			execvp(*cmdElem, cmdElem);
            exit(0);
		} else {
			if (background == 0) {
				int status;
				waitpid(pid, &status, WUNTRACED);
			} else {
				printf("%d\n", pid);
                background = 0;
			}
		}
	}
}

