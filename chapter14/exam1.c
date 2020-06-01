#include<stdio.h>
#include<unistd.h>
#include <errno.h>
#include <fcntl.h>
#include<stdlib.h>
char buf[500000];
void clr_fl(int fd, int flag);
void set_fl(int fd, int flag);
int main(void)
{
	int ntowrite, nwrite;
	char *ptr;
	ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
	fprintf(stderr, "read %d bytes\n", ntowrite);
	set_fl(STDOUT_FILENO, O_NONBLOCK);

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

	exit(0);
}

void clr_fl(int fd, int flag)
{
	int var;
	var=fcntl(fd, F_GETFL,0);
	var &= ~flag;
	fcntl(fd,F_SETFL,var);
}

void set_fl(int fd, int flag)
{
	int var;
	var=fcntl(fd,F_GETFL,0);
	var |= flag;
	fcntl(fd,F_SETFL,var);
}
