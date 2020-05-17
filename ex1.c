#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <errno.h>
#include <fcntl.h>
char buf[500000];

void set_fl(int fd, int flags)
{
	int var;
	if((var = fcntl(fd, F_GETFL,0))<0)
		printf("FCNTL F_GETFL error");

	var |= flags; /*turn on flags*/

	if(fcntl(fd, F_SETFL,0)<0)
		printf("fcntl F_SETFL error");
}

void clr_fl(int fd, int flags)
{
	int var;

	if((var = fcntl(fd, F_GETFL, 0))<0)
		printf("fcntl F_GETFL error");

	var &= ~ flags; /*turn off flags*/

	if(fcntl(fd, F_SETFL, 0)<0)
		printf("fcntl F_SETFL error");
}

int main(void)
{
	int ntowrite,nwrite;
	char *ptr;
	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);
	set_fl(STDOUT_FILENO, O_NONBLOCK);
	/* set nonblocking */
	ptr = buf;
	while (ntowrite > 0) {
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite);
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
		if (nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
	clr_fl(STDOUT_FILENO, O_NONBLOCK);
	/* clear nonblocking */
	exit(0);
}
