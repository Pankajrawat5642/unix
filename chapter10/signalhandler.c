#include<signal.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
static void sig_usr(int);
void err_sys(const char* X)
{
	perror(X);
	exit(1);
}

int main(void)
{
	if(signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR1");
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("cant catch SIGUSR2");
	for( ; ;)
		pause();
}

static void sig_usr(int signo)
{
	if(signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if(signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("This is signal %d\n",signo);

}

