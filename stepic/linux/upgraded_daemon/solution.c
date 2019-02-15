#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void demonize()
{
	chdir("/");
	setsid();
	close(stdin);
	close(stdout);
	close(stderr);
}

void sig_handler(int signo)
{
	exit(0);
}

int main()
{
	struct sigaction *sigact = malloc(sizeof(struct sigaction));
	sigact->sa_handler = sig_handler;
	sigaction(SIGURG, sigact, NULL);
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
