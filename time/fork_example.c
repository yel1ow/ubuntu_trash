#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void child_func_1()
{
	for(int i = 0; i < 10; i++)
	{
		printf("child process printed %d\n", i);
	}
}

void child_func_2()
{
	for(int i = 0; i < 5000; i++)
	{
		printf("child process printed %d\n", i);
	}
}

int main()
{
	pid_t pid_1 = fork();
	if(pid_1 == 0)
	{
		child_func_1();
		return 0;
	}
	pid_t pid_2 = fork();
	if(pid_2 == 0)
	{
		child_func_2();
		return 0;
	}
	wait(&pid_1);
	wait(&pid_2);
	return 0;
}