#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int fd1,fd2;
	struct stat sbuf;
	off_t fsz=0;
	int len;
	if(argc!=3)
	{
		printf("./a.out <file1> <file2>\n");
		exit(1);
	}
	else
	{
		fd1=open(argv[1],O_RDONLY);
		fd2=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0755);
		fstat(fd1,&sbuf);
		ftruncate(fd2,sbuf.st_size);
		int i=0;
		while(i==0)
		{
			void *adr1,*adr2;
			if((sbuf.st_size-fsz)>1024)
			{
				len=1024;
			}
			else
			{
				len=sbuf.st_size-fsz;
			}
			adr1=mmap(0,len,PROT_READ,MAP_SHARED,fd1,fsz);
			if(i==0)
			{
				close(fd1);
				i++;
			}
			adr2=mmap(0,len,PROT_WRITE,MAP_SHARED,fd2,fsz);
			memcpy(adr2,adr1,len);
			munmap(adr1,len);
			munmap(adr2,len);
			fsz+=len;
		}
	}
	return 0;
}
