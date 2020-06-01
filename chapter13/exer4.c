#include<stdio.h>
#include<sys/signal.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<syslog.h>
#include<sys/stat.h>
#include<sys/resource.h>
#include<pthread.h>
void daemonize(const char *cmd)
{
        int i, fd0, fd1, fd2;
        pid_t pid;
        struct rlimit rl;
        struct sigaction sa;

        umask(0);

        if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
                printf("%s: can’t get file limit", cmd);

        if ((pid = fork()) < 0)
                printf("%s: can’t fork", cmd);
        else if (pid != 0)
                exit(0);
        setsid();

        sa.sa_handler = SIG_IGN;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGHUP, &sa, NULL) < 0)
                printf("%s: can’t ignore SIGHUP", cmd);
        if ((pid = fork()) < 0)
                printf("%s: can’t fork", cmd);
        else if (pid != 0)
		exit(0);
        setsid();

        sa.sa_handler = SIG_IGN;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGHUP, &sa, NULL) < 0)
                printf("%s: can’t ignore SIGHUP", cmd);
        if ((pid = fork()) < 0)
                printf("%s: can’t fork", cmd);
        else if (pid != 0)
                exit(0);

        if (chdir("/") < 0)
                printf("%s: can’t change directory to /", cmd);
        if(rl.rlim_max == RLIM_INFINITY)
                rl.rlim_max = 1024;
        for (i = 0; i < rl.rlim_max; i++)
                close(i);
        fd0 = open("/dev/null", O_RDWR);
        fd1 = dup(0);
        fd2 = dup(0);

        openlog(cmd, LOG_CONS, LOG_DAEMON);
        if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
                syslog(LOG_ERR, "unexpected file descriptors %d %d %d",fd0, fd1, fd2);
        exit(1);
	}
}	

int main(int argc, char *argv[]) {
	int fd;
	char lname[15];

	daemonize(argv[0]);

	if ((fd = open("/home/pankaj/Desktop/unix/chapter13/pankaj.txt", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP)) < 0) {
		perror("open error");
		return -1;
	}

	if (getlogin_r(lname, 15) != 0) {
		perror("getlogin error");
		return -1;
	}

	if (write(fd, lname, strlen(lname)) < 0) {
		perror("write error");
		return -1;
	}

	return 0;
}
