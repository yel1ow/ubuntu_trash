#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

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

int proc_is_parent(pid_t x, pid_t parent)
{
	pid_t current = x;
	while (current != 1 && current != 0) 
	{
		if(current == parent)
			return 1;
		current = get_parent_pid(current);
	}
	if(current == parent)
		return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	int k = 0;
	DIR *dir = opendir("/proc");
	struct dirent *entry;
	while((entry = readdir(dir)) != 0)
	{
		if (entry->d_type && DT_DIR)
		{
			if(entry->d_name[0] >= '0' && entry->d_name[0] <= '9')
			{
				char path[100] = "/proc/";
				char tmp[50];
				strcat(path, entry->d_name);
				strcat(path, "/stat");
				FILE *f = fopen(path, "r");
				long long x;
				fscanf(f, "%lld ", &x);
				if(proc_is_parent(x, atoi(argv[1])))
					k++;
				fclose(f);
			}
		}
	}
	printf("%d\n", k);
	return 0;
}
