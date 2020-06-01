#include<stdio.h>
#include<time.h>
#include<sys/select.h>

int sleep(int ms)
{
	struct timeval tv;
        tv.tv_sec  = ms / 1000000;
        tv.tv_usec = ms % 1000000;
        return select(0, NULL, NULL, NULL, &tv);
}

int main(void)
{
	sleep(2000000);
}
