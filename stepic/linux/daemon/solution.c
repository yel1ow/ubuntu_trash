#include <stdio.h>
#include <unistd.h>

void demonize()
{
	chdir("/");
	setsid();
	close(stdin);
	close(stdout);
	close(stderr);
}

int main()
{
	pid_t pid;
	switch(pid = fork())
	{
		case 0:
			demonize();
			while(1);
			break;
		default:
			printf("%d\n", pid);
			return 0;
	}
}
