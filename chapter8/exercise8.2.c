#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void call();

int main()
{
	call();
	return 0;
}

int call()
{
	pid_t pid;
	if((pid = fork())<0)
	{
		printf("error");
		return ;
	}
	else if(pid == 0)
	{
		printf(" fork run success");
		return ;
	}

	printf("hello");
	return;
}


