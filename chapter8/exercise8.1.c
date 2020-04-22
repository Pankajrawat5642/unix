#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int globvar = 6;
int main(void)
{
	int var;
	pid_t pid;
	var = 88;
	printf("before vfork");
	if((pid = vfork()) < 0)
	{
		printf("vfork error");
	}
	else if(pid == 0)
	{
		globvar++;
		var++;
		fclose(stdout);
		exit(0);
	}

	printf("pid = %ld, glob = %d, var = %d\n",(long)getpid(), globvar, var);
	exit(0);

}


