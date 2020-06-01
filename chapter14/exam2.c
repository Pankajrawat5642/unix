#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(void)
{
	int fd,i;
	fd = open("/home/pankaj/Desktop/unix/chapter14/pankaj.txt",O_CREAT|O_RDWR|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP);
	for(i=1;i<100;i++)
	{
		write(fd,"PPP",3);
	}
	return 0;
}
