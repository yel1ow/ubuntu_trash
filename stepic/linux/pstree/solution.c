#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char *itoa_helper(char *dest, int i)
{
	if (i <= -10)
	{
    	dest = itoa_helper(dest, i/10);
  	}
  	*dest++ = '0' - i%10;
  	return dest;
}

char *itoa(char *dest, int i)
{
	char *s = dest;
	if (i < 0)
	{
  		*s++ = '-';
	}
	else
	{
		i = -i;
	}
	*itoa_helper(s, i) = '\0';
	return dest;
}

pid_t get_parent_pid(pid_t pid)
{
	char path[100] = "/proc/";
	char tmp[50];
	itoa(tmp, pid);
	strcat(path, tmp);
	strcat(path, "/stat");
	FILE *f = fopen(path, "r");
	long long x;
	fscanf(f, "%lld ", &x);
	char buf[100];
	fscanf(f, "%s ", buf);
	char state;
	fscanf(f, "%c ", &state);
	long long ppid;
	fscanf(f, "%lld ", &ppid);
	return ppid;
}

void print_process_parents(pid_t pid)
{
	pid_t current = pid;
	while (current != 1) 
	{
		printf("%d\n", current);
		current = get_parent_pid(current);
	}
	printf("%d\n", current);
}

int main(int argc, char *argv[])
{
	print_process_parents(atoi(argv[1]));
	return 0;
}
