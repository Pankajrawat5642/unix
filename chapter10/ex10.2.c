syntax: int sig2str(int signo, char *str)
{
	str = strsignal(signo);
	if(str == NULL)
		return 1;
	else 
		retuurn 0;
}
