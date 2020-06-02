#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/signal.h>
#include<stdlib.h>
extern char **environ;
void sigpipe(int signo);
int main(void)
{
	pid_t pid;
	//signal(SIGPIPE,sign);
	int i,fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	pid=vfork();
	int n;
	char line[100];
	if(pid>0)
	{
		close(fd1[0]);
		close(fd2[1]);
		while(fgets(line,100,stdin)!=NULL)
		{
			n=strlen(line);
			write(fd1[1],line,n);
			n=read(fd2[0],line,100);
			if(n==0)
			{
				break;
			}
			line[n]=0;
                	fputs(line,stdout);
		}
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);
		if(fd1[0]!=STDIN_FILENO)
		{
			dup2(fd1[0],STDIN_FILENO);
			close(fd1[0]);
		}
		if(fd2[1]!=STDOUT_FILENO)
		{
			dup2(fd2[1],STDOUT_FILENO);
			close(fd2[1]);
		}
		execl("./add2","add2",(char *)0);
	}
	return 0;
}

void sigpipe(int signo)
{
        printf("SIGPIPE caught\n");
        exit(1);
}

