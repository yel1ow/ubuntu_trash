#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int k1 = 0, k2 = 0;

void sig_handler(int signo)
{
	switch(signo)
	{
		case SIGUSR1:
			k1++;
			break;
		case SIGUSR2:
			k2++;
			break;
		case SIGTERM:
			printf("%d %d\n", k1, k2);
			exit(0);
	}
}

int main()
{
	struct sigaction *sigact = malloc(sizeof(struct sigaction));
	sigact->sa_handler = sig_handler;
	sigaction(SIGUSR1, sigact, NULL);
	sigaction(SIGUSR2, sigact, NULL);
	sigaction(SIGTERM, sigact, NULL);
	while(1);
	return 0;
}
